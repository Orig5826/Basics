#ifndef _PARSE_LINE_H_
#define _PARSE_LINE_H_

#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>

// public
void display(uint8_t * data,uint32_t len);

// alg demo
void sha1_demo(void);
void sha256_demo(void);
void sha512_demo(void);
// aes demo
void aes_demo(void);
void aes_cbc_demo(void);


#endif