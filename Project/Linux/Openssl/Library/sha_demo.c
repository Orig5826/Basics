/*
 * @breaf sha demo
 *     
 */
#include "alg_demo.h"
#include <openssl/sha.h>

void sha1_demo(void)
{
    const uint8_t data[] = "12345678";
    const uint32_t len = 8;
    uint8_t hash[20];

    SHA_CTX sha1_ctx;
    SHA1_Init(&sha1_ctx);
    SHA1_Update(&sha1_ctx,data,len);
    SHA1_Final(hash,&sha1_ctx);

    // display
    printf("-----  sha1_demo  -----\n");
    printf("data(str): %s\n",data);
    display(hash,20);
    printf("\n");
}

void sha256_demo(void)
{
    const uint8_t data[] = "12345678";
    const uint32_t len = 8;
    uint8_t hash[32];

    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx,data,len);
    SHA256_Final(hash,&sha256_ctx);

    // display
    printf("-----  sha256_demo  -----\n");
    printf("data(str): %s\n",data);
    display(hash,32);
    printf("\n");
}

void sha512_demo(void)
{
    const uint8_t data[] = "12345678";
    const uint32_t len = 8;
    uint8_t hash[64];

    SHA512_CTX sha512_ctx;
    SHA512_Init(&sha512_ctx);
    SHA512_Update(&sha512_ctx,data,len);
    SHA512_Final(hash,&sha512_ctx);

    // display
    printf("-----  sha512_demo  -----\n");
    printf("data(str): %s\n",data);
    display(hash,64);
    printf("\n");
}