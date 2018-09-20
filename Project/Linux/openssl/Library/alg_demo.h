/**
 * @brief 算法示例统一接口头文件
 * 
 * @file alg_demo.h
 * @author wenjf
 * @date 2018-09-20
 */
#ifndef _PARSE_LINE_H_
#define _PARSE_LINE_H_

#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>


// public
void display(const uint8_t * data,uint32_t len);
#define PRINT(explain,data,len)		{printf(explain);display(data,len);}



// alg demo
void sha1_demo(void);
void sha256_demo(void);
void sha512_demo(void);
// aes demo
void aes_demo(void);
void aes_cbc_demo(void);
// ecc
void ecdh_demo(void);
void ecdsa_demo(void);
// des
void des_demo(void);
void des_cbc_demo(void);

#endif