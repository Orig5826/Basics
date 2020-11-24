#pragma once

#include <Windows.h>

#include "stdio.h"
#include "stdlib.h"
#include "usbdisk.h"

#define SYMBOLIC_LINK	"HSEC    USBCOS"


#define PACKAGE_SIZE_MAX	(0x400)

typedef struct _stAPDU
{
	// ��ʼ����������Կ
	BOOL(*Initial)(void);
	// ��ȡ�����
	BOOL(*GetChallenge)(uint8_t * outBuf, uint32_t inlen);
	// ��ȡ��Կ
	BOOL(*GetPubkey)(uint8_t * outBuf, uint32_t * outLen);
	// Hash����
	BOOL(*Hash)(uint8_t * inBuf, uint32_t inLen, uint8_t *outHash, uint32_t *outHashLen);
	// ǩ������
	BOOL(*Sign)(uint8_t * inBuf, uint32_t inLen, uint8_t *outSign, uint32_t *outSignLen);
	// ��ǩ
	BOOL(*Verify)(uint8_t * inBuf, uint32_t inLen, uint8_t *inSign, uint32_t inSignLen);
	// ����
	BOOL(*Encrypt)(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen);
	// ����
	BOOL(*Decrypt)(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen);
}stAPDU;

void APDU_Initial(stAPDU * apdu);
void APDU_Exit();


// -------- test ---------------
void apdu_test();
void APDU_Test();


void usb_write_ff(HANDLE handle,uint8_t* data, uint32_t len);
void usb_read_ff(HANDLE handle, uint8_t* data, uint32_t* len);
