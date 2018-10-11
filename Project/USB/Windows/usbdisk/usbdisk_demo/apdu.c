#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
ע�⣺��ͷ�ļ����ٵ������Ƴ�����ֱ��ʹ����
usbdisk��ͷ�ļ�
*/
#include "usbdisk.h"
#pragma comment(lib,"usbdisk.lib")

#include "apdu.h"

// ---------------------------------------------------------------
#define BUFFER_SIZE_MAX	(0x400+0x40+8)	///< ��ǰ���ͺͽ��ܵ����ݵ�������

static uint8_t SendBuffer[BUFFER_SIZE_MAX];	///< ���ͻ�����
static uint8_t RecvBuffer[BUFFER_SIZE_MAX];
static uint32_t SendLength;
static uint32_t RecvLength;

static BOOL SendAPDU(uint8_t CLA, uint8_t INS, uint8_t P1, uint8_t P2, uint32_t Lc, uint8_t* data, uint32_t Le)
{
	// �ݶ������ֶΣ�Le,Lc����Ϊ1���ֽڣ���ΪĿǰû�з���̫��������
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
		printf("APDU �������ò���ȷ��\n");
		return FALSE;
	}
	// Send APDU
	usb_write(SendBuffer, SendLength);
	usb_read(RecvBuffer, &RecvLength);

	if (RecvBuffer[RecvLength - 2] != 0x90 && RecvBuffer[RecvLength - 1] != 0x00)
	{
		printf("���ط�9000�Ĵ��������ԭ��\n");
		return FALSE;
	}
	return TRUE;
}

static BOOL GetResponse(uint8_t *response, uint32_t * resLen)
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
	return TRUE;
}

static BOOL GetStatus(uint8_t SW[2])
{
	SW[0] = RecvBuffer[RecvLength - 2];
	SW[1] = RecvBuffer[RecvLength - 1];
	return TRUE;
}

/*
 * \breaf apdu����
 *
 */
void apdu_test()
{
	clock_t start, end;
	uint8_t data[1024] = { 0 };
	if (FALSE == usb_open())
	{
		printf("�豸��ʧ��");
		exit(-1);
	}

	start = clock();

	SendAPDU(0x00, 0x84, 0x00, 0x00, 0, NULL, 1024);

	// ����
	// SendAPDU(0x00, 0x41, 0x00, 0xff, 1024, data, 1024 + 8);

	end = clock();
	printf("��ʱ: %fs\n", (double)(end - start) / CLK_TCK);
	usb_close();
}

// -----------------------------------------------------------------------
//

// ��ʼ����������Կ
static BOOL Initial(void)
{
	// ����SM2 ��Կ��
	SendAPDU(0x00, 0x20, 0x00, 0x00, 0, NULL, 0);
	// ����SM4 KEY��IV
	SendAPDU(0x00, 0x20, 0x00, 0x01, 0, NULL, 0);
	return TRUE;
}

// ��ȡ�����
static BOOL GetChallenge(uint8_t * outBuf, uint32_t Len)
{
	uint32_t length = 0;
	if (Len > PACKAGE_SIZE_MAX)
	{
		return FALSE;
	}
	SendAPDU(0x00, 0x84, 0x00, 0x00, 0, NULL, Len);
	GetResponse(outBuf, &length);
	if (Len != length)
	{
		return FALSE;
	}
	return TRUE;
}

// ��ȡ��Կ
BOOL GetPubkey(uint8_t * outBuf, uint32_t * outLen)
{
	SendAPDU(0x00, 0x21, 0x00, 0x00, 0, NULL, 0x40);
	GetResponse(outBuf, outLen);
	return TRUE;
}

// Hash����
BOOL Hash_SM3(uint8_t * inBuf, uint32_t inLen, uint8_t *outHash, uint32_t *outHashLen)
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
	return TRUE;
}

// ǩ������
BOOL Sign_SM2(uint8_t * inBuf, uint32_t inLen, uint8_t *outSign, uint32_t *outSignLen)
{
	uint8_t hash[32];
	uint32_t hashLen;
	Hash_SM3(inBuf, inLen, hash, &hashLen);

	SendAPDU(0x00, 0x31, 0x00, 0x00, 0, NULL, 0x40);
	GetResponse(outSign, outSignLen);
	return TRUE;
}
// ��ǩ
BOOL Verify_SM2(uint8_t * inBuf, uint32_t inLen, uint8_t *inSign, uint32_t inSignLen)
{
	uint8_t hash[32];
	uint32_t hashLen;
	Hash_SM3(inBuf, inLen, hash, &hashLen);

	SendAPDU(0x00, 0x32, 0x00, 0x00, inSignLen, inSign, 0);
	return TRUE;
}
// ����
BOOL Encrypt_SM4(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen)
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
			printf("Decrypt_SM4 �������ʧ��\n");
			return FALSE;
		}
		inLen -= PACKAGE_SIZE_MAX;
		index += PACKAGE_SIZE_MAX;
		*outLen += length;
	}
	// SM3 hashLen = 32
	SendAPDU(0x00, 0x41, 0x00, 0xFF, inLen, inBuf + index, inLen + 16);
	GetResponse(outBuf + index, &length);
	*outLen += length;

	return TRUE;
}
// ����
BOOL Decrypt_SM4(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen)
{
	uint32_t length = 0;
	uint32_t index = 0;
	if (inLen % 16 != 0)
	{
		printf("Decrypt_SM4 ���ĳ��Ȳ���ȷ\n");
		return FALSE;
	}
	*outLen = 0;
	while (inLen > PACKAGE_SIZE_MAX)
	{
		SendAPDU(0x00, 0x42, 0x00, 0x00, PACKAGE_SIZE_MAX, inBuf + index, PACKAGE_SIZE_MAX);
		GetResponse(outBuf + index, &length);
		if (length != PACKAGE_SIZE_MAX)
		{
			printf("Decrypt_SM4 �������ʧ��\n");
			return FALSE;
		}
		inLen -= PACKAGE_SIZE_MAX;
		index += PACKAGE_SIZE_MAX;
		*outLen += length;
	}
	// SM3 hashLen = 32
	SendAPDU(0x00, 0x42, 0x00, 0xFF, inLen, inBuf + index, inLen);
	GetResponse(outBuf + index, &length);
	*outLen += length;
	return TRUE;
}






// ----------------------------------------------------------------------------------
void APDU_Initial(stAPDU * apdu)
{
	if (TRUE != usb_open())
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