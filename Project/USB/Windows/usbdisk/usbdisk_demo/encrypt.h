
#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_
#include "apdu.h"

void GenerateKey(void);
void Encrypt(const char * fname_in, const char * fname_out);
void Decrypt(const char * fname_in, const char * fname_out);

void Encrypt_Test(void);
#endif
