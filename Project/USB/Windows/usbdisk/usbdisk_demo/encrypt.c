
#include "encrypt.h"
#include <stdlib.h>

// SM4 Block Size = 16 Bytes
#define GET_CIPHER_LEN(plain_len) (plain_len + (16 - plain_len % 16))
#define SM2_SIGN_SIZE	64

void GenerateKey(void)
{
	stAPDU apdu;
	APDU_Initial(&apdu);

	apdu.Initial();

	// 关闭APDU通讯指令
	APDU_Exit();
}

void Encrypt(const char * fname_in,const char * fname_out)
{
	uint32_t file_length = 0;
	uint8_t * pInContent = NULL, * pOutContent = NULL;
	uint32_t cipher_length = 0,length = 0;

	stAPDU apdu;

	// Open File
	FILE * pIn, *pOut;
	pIn = fopen(fname_in, "rb");
	if(pIn == NULL)
	{
		printf("文件[%s]打开失败，请确认该文件是否存在\n", fname_in);
		exit(-1);
	}
	pOut = fopen(fname_out, "wb");
	if (pOut == NULL)
	{
		printf("文件[%s]打开失败，请查找原因\n", fname_out);
		exit(-1);
	}

	// 开启APDU通讯指令
	APDU_Initial(&apdu);
	fseek(pIn, 0, SEEK_END);
	file_length = ftell(pIn);
	pInContent = (uint8_t *)malloc((file_length + SM2_SIGN_SIZE) * sizeof(uint8_t));
	fseek(pIn, 0, SEEK_SET);
	fread(pInContent, sizeof(uint8_t), file_length, pIn);

	// -------------------
	// 在加密前，在文件的结尾附加签名结果
	apdu.Sign(pInContent, file_length, pInContent + file_length, &length);
	if(length != SM2_SIGN_SIZE)
	{
		printf("签名结果长度错误\n");
		exit(-1);
	}
	file_length += SM2_SIGN_SIZE;		//明文长度 + 签名值长度

	cipher_length = GET_CIPHER_LEN(file_length);
	pOutContent = (uint8_t *)malloc(cipher_length * sizeof(uint8_t));
	apdu.Encrypt(pInContent, file_length, pOutContent, &length);
	if (cipher_length != length)
	{
		printf("密文长度计算错误？\n");
	}
	fwrite(pOutContent, sizeof(uint8_t), length, pOut);

	// 关闭APDU通讯指令
	APDU_Exit();

	fclose(pIn);
	fclose(pOut);
}


void Decrypt(const char * fname_in, const char * fname_out)
{
	uint32_t file_length = 0;
	uint8_t * pInContent = NULL, *pOutContent = NULL;
	uint32_t length = 0;

	stAPDU apdu;

	// Open File
	FILE * pIn, *pOut;
	pIn = fopen(fname_in, "rb");
	if (pIn == NULL)
	{
		printf("文件[%s]打开失败，请确认该文件是否存在\n", fname_in);
		exit(-1);
	}
	pOut = fopen(fname_out, "wb");
	if (pOut == NULL)
	{
		printf("文件[%s]打开失败，请查找原因\n", fname_out);
		exit(-1);
	}

	// 开启APDU通讯指令
	APDU_Initial(&apdu);

	fseek(pIn, 0, SEEK_END);
	file_length = ftell(pIn);
	if (file_length % 16 != 0)
	{
		printf("请确认密文文件长度是否有问题？\n");
	}
	pInContent = (uint8_t *)malloc(file_length * sizeof(uint8_t));
	fseek(pIn, 0, SEEK_SET);
	fread(pInContent, sizeof(uint8_t), file_length, pIn);

	// 因为明文长度 <= 密文长度
	length = file_length;
	pOutContent = (uint8_t *)malloc(file_length * sizeof(uint8_t));
	apdu.Decrypt(pInContent, file_length, pOutContent, &length);
	
	// -------------------
	// 解密完成之前验证签名是否正确，若不正确，则什么都不写入文件
	if(TRUE != apdu.Verify(pOutContent, length - SM2_SIGN_SIZE, pOutContent + length- SM2_SIGN_SIZE,SM2_SIGN_SIZE))
	{
		printf("签名验证失败！\n");
		exit(-1);
	}
	length -= SM2_SIGN_SIZE;	//明文长度 = 总长 - 签名值长度

	fwrite(pOutContent, sizeof(uint8_t), length, pOut);

	// 关闭APDU通讯指令
	APDU_Exit();

	fclose(pIn);
	fclose(pOut);
}


void Encrypt_Test(void)
{
	// 仅仅用来做测试使用
	Encrypt("usbdisk.h", "cipher");
	Decrypt("cipher","plain");
}
