#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "usbdrv.h"
#include "apdu.h"

// ---------------------------------------------------------------
#define BUFFER_SIZE_MAX	(0x400+0x40+8)	///< 当前发送和接受的数据的最大个数

static uint8_t SendBuffer[BUFFER_SIZE_MAX];	///< 发送缓存区
static uint8_t RecvBuffer[BUFFER_SIZE_MAX];
static uint32_t SendLength;
static uint32_t RecvLength;

static bool SendAPDU(uint8_t CLA, uint8_t INS, uint8_t P1, uint8_t P2, uint32_t Lc, uint8_t* data, uint32_t Le)
{
	// 暂定长度字段（Le,Lc）都为1个字节，因为目前没有发送太长的数据
	memset(SendBuffer, 0x00, BUFFER_SIZE_MAX);
	memset(RecvBuffer, 0x00, BUFFER_SIZE_MAX);
	SendLength = 0;
	RecvLength = BUFFER_SIZE_MAX;
	SendBuffer[0] = CLA;
	SendBuffer[1] = INS;
	SendBuffer[2] = P1;
	SendBuffer[3] = P2;
	if (Lc == 0x00 && data == NULL && Le == 0x00)
	{
		// CASE1
		SendLength = 4;
	}
	else if (Lc == 0x00 && data == NULL && Le != 0x00)
	{
		//CASE2
		if (Le < 256)
		{
			SendBuffer[4] = Le;
			SendLength = 4 + 1;
		}
		else
		{
			SendBuffer[4] = 0x00;
			SendBuffer[5] = (Le >> 8) & 0xff;
			SendBuffer[6] = Le & 0xff;
			SendLength = 4 + 3;
		}
	}
	else if (Lc != 0x00 && data != NULL && Le == 0x00)
	{
		if (Lc < 256)
		{
			SendBuffer[4] = Lc;
			memcpy(SendBuffer + 5, data, Lc);
			SendLength = 4 + 1 + Lc;
		}
		else
		{
			SendBuffer[4] = 0x00;
			SendBuffer[5] = (Lc >> 8) & 0xff;
			SendBuffer[6] = Lc & 0xff;
			memcpy(SendBuffer + 7, data, Lc);
			SendLength = 4 + 3 + Lc;
		}
	}
	else if (Lc != 0x00 && data != NULL && Le != 0x00)
	{
		if (Lc < 256)
		{
			SendBuffer[4] = Lc;
			memcpy(SendBuffer + 5, data, Lc);
			SendLength = 4 + 1 + Lc;
		}
		else
		{
			SendBuffer[4] = 0x00;
			SendBuffer[5] = (Lc >> 8) & 0xff;
			SendBuffer[6] = Lc & 0xff;
			memcpy(SendBuffer + 7, data, Lc);
			SendLength = 4 + 3 + Lc;
		}

		if (Le < 256)
		{
			SendBuffer[SendLength] = Le;
			SendLength = SendLength + 1;
		}
		else
		{
			SendBuffer[SendLength] = 0x00;
			SendBuffer[SendLength + 1] = (Le >> 8) & 0xff;
			SendBuffer[SendLength + 2] = Le & 0xff;
			SendLength = SendLength + 3;
		}
	}
	else
	{
		printf("APDU 参数配置不正确！\n");
		return False;
	}
	// Send APDU
	usb_write(SendBuffer, SendLength);
	usb_read(RecvBuffer, &RecvLength);

	if (RecvBuffer[RecvLength - 2] != 0x90 && RecvBuffer[RecvLength - 1] != 0x00)
	{
		printf("返回非9000的错误，请查找原因\n");
		return False;
	}
	return True;
}

static bool GetResponse(uint8_t *response, uint32_t * resLen)
{
	if (RecvLength > 2)
	{
		*resLen = RecvLength - 2;
		memcpy(response, RecvBuffer, *resLen);
	}
	else
	{
		*resLen = 0;
		response = NULL;
	}
	return True;
}

static bool GetStatus(uint8_t SW[2])
{
	SW[0] = RecvBuffer[RecvLength - 2];
	SW[1] = RecvBuffer[RecvLength - 1];
	return True;
}

/*
 * \breaf apdu命令
 *
 */
void apdu_test()
{
	clock_t start, end;
	uint8_t data[1024] = { 0 };
	if (False == usb_open(USB_VID,USB_PID))
	{
		printf("设备打开失败");
		exit(-1);
	}

	start = clock();

	SendAPDU(0x00, 0x84, 0x00, 0x00, 0, NULL, 1024);

	// 加密
	SendAPDU(0x00, 0x41, 0x00, 0xff, 1024, data, 1024 + 8);

	end = clock();
	printf("计时: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	usb_close();
}

// -----------------------------------------------------------------------
//

// 初始化，生成密钥
static bool Initial(void)
{
	// 生成SM2 密钥对
	SendAPDU(0x00, 0x20, 0x00, 0x00, 0, NULL, 0);
	// 生成SM4 KEY和IV
	SendAPDU(0x00, 0x20, 0x00, 0x01, 0, NULL, 0);
	return True;
}

// 获取随机数
static bool GetChallenge(uint8_t * outBuf, uint32_t Len)
{
	uint32_t length = 0;
	if (Len > PACKAGE_SIZE_MAX)
	{
		return False;
	}
	SendAPDU(0x00, 0x84, 0x00, 0x00, 0, NULL, Len);
	GetResponse(outBuf, &length);
	if (Len != length)
	{
		return False;
	}
	return True;
}

// 获取公钥
bool GetPubkey(uint8_t * outBuf, uint32_t * outLen)
{
	SendAPDU(0x00, 0x21, 0x00, 0x00, 0, NULL, 0x40);
	GetResponse(outBuf, outLen);
	return True;
}

// Hash计算
bool Hash_SM3(uint8_t * inBuf, uint32_t inLen, uint8_t *outHash, uint32_t *outHashLen)
{
	uint32_t index = 0;
	// Hash Start
	SendAPDU(0x00, 0x30, 0x00, 0x00, 0, NULL, 0);

	while (inLen > PACKAGE_SIZE_MAX)
	{
		SendAPDU(0x00, 0x30, 0x00, 0x01, PACKAGE_SIZE_MAX, inBuf + index, 0);
		inLen -= PACKAGE_SIZE_MAX;
		index += PACKAGE_SIZE_MAX;
	}
	// SM3 hashLen = 32
	SendAPDU(0x00, 0x30, 0x00, 0xFF, inLen, inBuf + index, 32);
	GetResponse(outHash, outHashLen);
	return True;
}

// 签名计算
bool Sign_SM2(uint8_t * inBuf, uint32_t inLen, uint8_t *outSign, uint32_t *outSignLen)
{
	uint8_t hash[32];
	uint32_t hashLen;
	Hash_SM3(inBuf, inLen, hash, &hashLen);

	SendAPDU(0x00, 0x31, 0x00, 0x00, 0, NULL, 0x40);
	GetResponse(outSign, outSignLen);
	return True;
}
// 验签
bool Verify_SM2(uint8_t * inBuf, uint32_t inLen, uint8_t *inSign, uint32_t inSignLen)
{
	uint8_t hash[32];
	uint32_t hashLen;
	Hash_SM3(inBuf, inLen, hash, &hashLen);

	SendAPDU(0x00, 0x32, 0x00, 0x00, inSignLen, inSign, 0);
	return True;
}
// 加密
bool Encrypt_SM4(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen)
{
	uint32_t length = 0;
	uint32_t index = 0;

	*outLen = 0;
	while (inLen > PACKAGE_SIZE_MAX)
	{
		SendAPDU(0x00, 0x41, 0x00, 0x00, PACKAGE_SIZE_MAX, inBuf + index, PACKAGE_SIZE_MAX);
		GetResponse(outBuf + index, &length);
		if (length != PACKAGE_SIZE_MAX)
		{
			printf("Decrypt_SM4 多包加密失败\n");
			return False;
		}
		inLen -= PACKAGE_SIZE_MAX;
		index += PACKAGE_SIZE_MAX;
		*outLen += length;
	}
	// SM3 hashLen = 32
	SendAPDU(0x00, 0x41, 0x00, 0xFF, inLen, inBuf + index, inLen + 16);
	GetResponse(outBuf + index, &length);
	*outLen += length;

	return True;
}
// 解密
bool Decrypt_SM4(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen)
{
	uint32_t length = 0;
	uint32_t index = 0;
	if (inLen % 16 != 0)
	{
		printf("Decrypt_SM4 密文长度不正确\n");
		return False;
	}
	*outLen = 0;
	while (inLen > PACKAGE_SIZE_MAX)
	{
		SendAPDU(0x00, 0x42, 0x00, 0x00, PACKAGE_SIZE_MAX, inBuf + index, PACKAGE_SIZE_MAX);
		GetResponse(outBuf + index, &length);
		if (length != PACKAGE_SIZE_MAX)
		{
			printf("Decrypt_SM4 多包解密失败\n");
			return False;
		}
		inLen -= PACKAGE_SIZE_MAX;
		index += PACKAGE_SIZE_MAX;
		*outLen += length;
	}
	// SM3 hashLen = 32
	SendAPDU(0x00, 0x42, 0x00, 0xFF, inLen, inBuf + index, inLen);
	GetResponse(outBuf + index, &length);
	*outLen += length;
	return True;
}






// ----------------------------------------------------------------------------------
void APDU_Initial(stAPDU * apdu)
{
	if (True != usb_open(USB_VID,USB_PID))
	{
		exit(-1);
	}
	usb_set_debug_level(2);

	apdu->Initial = Initial;
	apdu->GetChallenge = GetChallenge;
	apdu->GetPubkey = GetPubkey;
	apdu->Hash = Hash_SM3;
	apdu->Sign = Sign_SM2;
	apdu->Verify = Verify_SM2;
	apdu->Encrypt = Encrypt_SM4;
	apdu->Decrypt = Decrypt_SM4;
}

void APDU_Exit(void)
{
	usb_close();
}

void APDU_Test()
{
	uint8_t i = 0;
	uint8_t buf[1024 + 0x40];
	uint8_t sign[64];
	uint32_t signLen = 0;
	uint8_t cipher[1024 + 0x40];
	uint8_t result[1024 + 0x40];
	uint32_t cLen, rLen;

	stAPDU apdu;
	APDU_Initial(&apdu);

	apdu.Initial();
	apdu.GetChallenge(buf, 8);

	memset(buf, 0x00, 1024);
	for (i = 0; i < 3; i++)
	{
		buf[i] = 0x61 + i;
	}
	// 
	apdu.Sign(buf, 3, sign, &signLen);
	apdu.Verify(buf, 3, sign, signLen);

	//
	apdu.Encrypt(buf, 3, cipher, &cLen);
	apdu.Decrypt(cipher, cLen, result, &rLen);
}