/**
 * @file hmac_demo.c
 * @author wenjf
 * @brief HMAC 算法Demo示例
 * @version 0.1
 * @date 2018-10-12
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "alg_demo.h"
#include <openssl/hmac.h>


void hmac_sha256_demo(void)
{
    uint8_t key[] = "012345678";
    uint8_t data[] = "hello world";
    uint32_t key_len = sizeof(key) - 1;
    uint32_t data_len = sizeof(data) - 1;
    uint8_t hmac_result[EVP_MAX_MD_SIZE];
    uint32_t hmac_resLen = 0;
    /* 配置算法 */
    const EVP_MD * engine = NULL;
    engine = EVP_sha256();

    /* HMAC 运算 */
    {
        HMAC_CTX * ctx;
        ctx = HMAC_CTX_new();
        HMAC_Init_ex(ctx, key, key_len, engine, NULL);
        HMAC_Update(ctx, data, data_len);
        HMAC_Final(ctx, hmac_result, &hmac_resLen);

        printf("KEY\n");
        display(key,key_len);
        printf("DATA\n");
        display(data,data_len);
        printf("HMAC_SHA256\n");
        display(hmac_result,hmac_resLen);

        HMAC_CTX_free(ctx);
    }

}