
#include "demo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE		0xC000				//48k
#define FPLAIN_SIZE		(BLOCK_SIZE * 4)	//192k
#define FPLAIN		"plain.bin"
#define FCRYPT		"crypt_ecb.bin"
#define FRESULT		"result.bin"

void CreatePlainFile()
{
	FILE * pf;
	const uint8_t data[16] = {
			0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
			0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	pf = fopen(FPLAIN,"wb");
	if(NULL == pf)
	{
		printf("文件%s创建失败\n",FPLAIN);
		exit(-1);
	}
	for(uint32_t i = 0; i < FPLAIN_SIZE; i+=16)
	{
		fwrite(data,16,sizeof(uint8_t),pf);
	}
	fclose(pf);
}

void Encrypt_SM4_ECB()
{
	FILE * pf;
	FILE * pfcrypt;
	uint8_t * pData = NULL;
	uint8_t * pResult = NULL;
	uint32_t rLen;
	uint32_t DataLength = 0;
	uint8_t apdu[5] = {0x00,0xC2,0x00,0x00,0x00};
	pf = fopen(FPLAIN,"rb");
	if(NULL == pf)
	{
		printf("文件%s打开失败\n",FPLAIN);
		exit(-1);
	}

	pfcrypt = fopen(FCRYPT,"wb");
	if(NULL == pf)
	{
		printf("文件%s创建失败\n",FCRYPT);
		exit(-1);
	}

	fseek(pf,0L,SEEK_END);
	DataLength = ftell(pf);
	if(DataLength % BLOCK_SIZE != 0)
	{
		printf("文件长度错误！\n");
		exit(-1);
	}

	pData = (uint8_t *)malloc(BLOCK_SIZE * sizeof(uint8_t));
	pResult = (uint8_t *)malloc(BLOCK_SIZE * sizeof(uint8_t));
	fseek(pf,0L,SEEK_SET);
	for(uint32_t i = 0; i < DataLength; i += BLOCK_SIZE)
	{
		fread(pData,BLOCK_SIZE,sizeof(uint8_t),pf);
		// 加密处理
		usb_write_hs(apdu,5,pData,BLOCK_SIZE);
		rLen = BLOCK_SIZE;
		usb_read_hs(apdu,5,pResult,&rLen);
		//
		fwrite(pResult,BLOCK_SIZE,sizeof(uint8_t),pfcrypt);
	}

	free(pData);
	free(pResult);

	fclose(pfcrypt);
	fclose(pf);
}


void Decrypt_SM4_ECB()
{
	FILE * pfcrypt;
	FILE * pfresult;
	uint8_t * pData = NULL;
	uint8_t * pResult = NULL;
	uint32_t rLen;
	uint32_t DataLength = 0;
	uint8_t apdu[5] = {0x00,0xC4,0x00,0x00,0x00};
	pfcrypt = fopen(FCRYPT,"rb");
	if(NULL == pfcrypt)
	{
		printf("文件%s打开失败\n",FCRYPT);
		exit(-1);
	}

	pfresult = fopen(FRESULT,"wb");
	if(NULL == pfresult)
	{
		printf("文件%s创建失败\n",FRESULT);
		exit(-1);
	}

	fseek(pfcrypt,0L,SEEK_END);
	DataLength = ftell(pfcrypt);
	if(DataLength % BLOCK_SIZE != 0)
	{
		printf("文件长度错误！\n");
		exit(-1);
	}

	pData = (uint8_t *)malloc(BLOCK_SIZE * sizeof(uint8_t));
	pResult = (uint8_t *)malloc(BLOCK_SIZE * sizeof(uint8_t));
	fseek(pfcrypt,0L,SEEK_SET);
	for(uint32_t i = 0; i < DataLength; i += BLOCK_SIZE)
	{
		fread(pData,BLOCK_SIZE,sizeof(uint8_t),pfcrypt);
		// 加密处理
		usb_write_hs(apdu,5,pData,BLOCK_SIZE);
		rLen = BLOCK_SIZE;
		usb_read_hs(apdu,5,pResult,&rLen);
		//
		fwrite(pResult,BLOCK_SIZE,sizeof(uint8_t),pfresult);
	}

	free(pData);
	free(pResult);

	fclose(pfcrypt);
	fclose(pfresult);
}

void PlainCompare()
{
	FILE * pf;
	FILE * pfresult;
	uint8_t * pData = NULL;
	uint8_t * pResult = NULL;
	uint32_t plain_len,result_len,len;
	pf = fopen(FPLAIN,"rb");
	if(NULL == pf)
	{
		printf("文件%s打开失败\n",FPLAIN);
		exit(-1);
	}
	pfresult = fopen(FRESULT,"rb");
	if(NULL == pfresult)
	{
		printf("文件%s打开失败\n",FRESULT);
		exit(-1);
	}

	fseek(pf,0L,SEEK_END);
	plain_len = ftell(pf);
	fseek(pfresult,0L,SEEK_END);
	result_len = ftell(pfresult);
	if(plain_len != result_len)
	{
		printf("明文文件和解密后的文件长度不等，肯定出错了\n");
		exit(-1);
	}
	len = plain_len;

	pData = (uint8_t *)malloc(len * sizeof(uint8_t));
	pResult = (uint8_t *)malloc(len * sizeof(uint8_t));

	fseek(pf,0L,SEEK_SET);
	fseek(pfresult,0L,SEEK_SET);
	// 读文件全部内容
	fread(pData,len,sizeof(uint8_t),pf);
	fread(pResult,len,sizeof(uint8_t),pfresult);

	if(0 != memcmp(pData,pResult,len))
	{
		printf("明文文件和解密后的内容不一致\n");
	}
	else
	{
		printf("SM4_ECB 加解密操作完成\n");
	}

	free(pData);
	free(pResult);

	fclose(pfresult);
	fclose(pf);
}

void hs_demo(void)
{
	if (False == usb_open(USB_VID, USB_PID))
	{
		return;
	}
	usb_set_debug_level(0);

	// 用来测试的明文文件
	CreatePlainFile();
	Encrypt_SM4_ECB();
	Decrypt_SM4_ECB();
	PlainCompare();

	usb_close();
}