#pragma once

#include "encrypt.h"
#include <stdlib.h>

// SM4 Block Size = 16 Bytes
#define GET_CIPHER_LEN(plain_len) (plain_len + (16 - plain_len % 16))

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
		printf("�ļ�[%s]��ʧ�ܣ���ȷ�ϸ��ļ��Ƿ����\n", fname_in);
		exit(-1);
	}
	pOut = fopen(fname_out, "wb");
	if (pOut == NULL)
	{
		printf("�ļ�[%s]��ʧ�ܣ������ԭ��\n", fname_out);
		exit(-1);
	}

	// ����APDUͨѶָ��
	APDU_Initial(&apdu);

	fseek(pIn, 0, SEEK_END);
	file_length = ftell(pIn);
	pInContent = (uint8_t *)malloc(file_length * sizeof(uint8_t));
	fseek(pIn, 0, SEEK_SET);
	fread(pInContent, sizeof(uint8_t), file_length, pIn);

	cipher_length = GET_CIPHER_LEN(file_length);
	pOutContent = (uint8_t *)malloc(cipher_length * sizeof(uint8_t));
	apdu.Encrypt(pInContent, file_length, pOutContent, &length);
	if (cipher_length != length)
	{
		printf("���ĳ��ȼ������\n");
	}
	fwrite(pOutContent, sizeof(uint8_t), length, pOut);

	// �ر�APDUͨѶָ��
	APDU_Exit();

	fclose(pIn);
	fclose(pOut);
}


void Decrypt(const char * fname_in, const char * fname_out)
{
	uint32_t file_length = 0;
	uint8_t * pInContent = NULL, *pOutContent = NULL;
	uint32_t cipher_length = 0;

	stAPDU apdu;

	// Open File
	FILE * pIn, *pOut;
	pIn = fopen(fname_in, "rb");
	if (pIn == NULL)
	{
		printf("�ļ�[%s]��ʧ�ܣ���ȷ�ϸ��ļ��Ƿ����\n", fname_in);
		exit(-1);
	}
	pOut = fopen(fname_out, "wb");
	if (pOut == NULL)
	{
		printf("�ļ�[%s]��ʧ�ܣ������ԭ��\n", fname_out);
		exit(-1);
	}

	// ����APDUͨѶָ��
	APDU_Initial(&apdu);

	fseek(pIn, 0, SEEK_END);
	file_length = ftell(pIn);
	if (file_length % 16 != 0)
	{
		printf("��ȷ�������ļ������Ƿ������⣿\n");
	}
	pInContent = (uint8_t *)malloc(file_length * sizeof(uint8_t));
	fseek(pIn, 0, SEEK_SET);
	fread(pInContent, sizeof(uint8_t), file_length, pIn);

	// ��Ϊ���ĳ��� <= ���ĳ���
	cipher_length = file_length;
	pOutContent = (uint8_t *)malloc(file_length * sizeof(uint8_t));
	apdu.Decrypt(pInContent, file_length, pOutContent, &cipher_length);
	fwrite(pOutContent, sizeof(uint8_t), cipher_length, pOut);

	// �ر�APDUͨѶָ��
	APDU_Exit();

	fclose(pIn);
	fclose(pOut);
}
