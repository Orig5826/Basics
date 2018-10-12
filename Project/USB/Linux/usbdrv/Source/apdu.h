
#ifndef _APDU_H_
#define _APDU_H_

#include <stdio.h>
#include <stdlib.h>

#include "demo.h"
#include "usbdrv.h"

#define PACKAGE_SIZE_MAX	(0x400)

typedef struct _stAPDU
{
	// 初始化，生成密钥
	bool(*Initial)(void);
	// 获取随机数
	bool(*GetChallenge)(uint8_t * outBuf, uint32_t inlen);
	// 获取公钥
	bool(*GetPubkey)(uint8_t * outBuf, uint32_t * outLen);
	// Hash计算
	bool(*Hash)(uint8_t * inBuf, uint32_t inLen, uint8_t *outHash, uint32_t *outHashLen);
	// 签名计算
	bool(*Sign)(uint8_t * inBuf, uint32_t inLen, uint8_t *outSign, uint32_t *outSignLen);
	// 验签
	bool(*Verify)(uint8_t * inBuf, uint32_t inLen, uint8_t *inSign, uint32_t inSignLen);
	// 加密
	bool(*Encrypt)(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen);
	// 解密
	bool(*Decrypt)(uint8_t * inBuf, uint32_t inLen, uint8_t *outBuf, uint32_t *outLen);
}stAPDU;

void APDU_Initial(stAPDU * apdu);
void APDU_Exit();


// -------- test ---------------
void apdu_test();
void APDU_Test();

#endif
