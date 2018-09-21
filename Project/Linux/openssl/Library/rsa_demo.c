/**
 * @brief res 算法Demo示例
 * 
 * @file rsa_demo.c
 * @author wenjf
 * @date 2018-09-21
 */

#include "alg_demo.h"
#include <openssl/rsa.h>

void rsa_demo(void)
{
    RSA * rsa;
    int keySize;
    BIGNUM * e;
    const BIGNUM * d, * n;
    const BIGNUM *p,*q,*dp,*dq,*u;
    // 待加密的数据
    uint8_t data[] = "aaabbbccdskjkfd";
    const uint32_t data_len = sizeof(data) - 1;
    uint8_t cipher[128];
    uint8_t result[128];
    uint8_t pkcs1_padding[128];
    int len;
    PRINT("data:",data,data_len);

    /* 生成密钥对 */
    rsa = RSA_new();

    e = BN_new();
    BN_set_word(e,65537);
    RSA_generate_key_ex(rsa,1024,e,NULL);

    /*-----  获取公钥和私钥  -------*/
    /* RSA_CRT模式 */
    p = RSA_get0_p(rsa);
    q = RSA_get0_q(rsa);
    dp = RSA_get0_dmp1(rsa);
    dq = RSA_get0_dmq1(rsa);
    u = RSA_get0_iqmp(rsa);
    
    printf("p = \n");
    BN_print_fp(stdout,p);
    printf("\n");
    printf("q = \n");
    BN_print_fp(stdout,q);
    printf("\n");
    printf("dp = \n");
    BN_print_fp(stdout,dp);
    printf("\n");
    printf("dq = \n");
    BN_print_fp(stdout,dq);
    printf("\n");
    printf("du = \n");
    BN_print_fp(stdout,u);
    printf("\n");


    /* RSA_ND 模式 */
    d = RSA_get0_d(rsa);
    n = RSA_get0_n(rsa);

    printf("私钥d：\n");
    BN_print_fp(stdout,d);
    printf("\n");
    printf("公钥n：\n");
    BN_print_fp(stdout,n);
    printf("\n");

    /* 获取密钥大小 */
    keySize = RSA_size(rsa);
    printf("keySize = %d\n",keySize);

#if 1
    /* 
        此处的目的是查看下pkcs1 padding后的结果，用于上层判断验证密文是否正确
        经过验证，我自己填充的数据，加密后的密文和标准的一致。
    */
    // 0001 FF...FF 00 DATA 
    RSA_padding_add_PKCS1_type_1(pkcs1_padding,128,data,data_len);
    PRINT("pkcs1_padding_type1 :",pkcs1_padding,128);
    // 0002 非0随机数... 00 DATA
    // RSA_padding_add_PKCS1_type_2(pkcs1_padding,128,data,data_len);
    // PRINT("pkcs1_padding_type2 :",pkcs1_padding,128);

    // 直接使用我自己填充好的数据填充
    len = RSA_public_encrypt(128, pkcs1_padding, cipher, rsa, RSA_NO_PADDING);
    PRINT("pkcs1_padding  cipher",cipher,len);
    len = RSA_private_decrypt(128, cipher,result, rsa, RSA_NO_PADDING);
    PRINT("pkcs1_padding  result",result,len);

#else
    /* Openssl 中自带的RSA_PKCS1_PADDING具体的填充方式是什么样的？*/
    len = RSA_public_encrypt(data_len, data, cipher, rsa, RSA_PKCS1_PADDING);
    PRINT("pkcs1_padding  cipher",cipher,len);

    len = RSA_private_decrypt(128, cipher,result, rsa, RSA_PKCS1_PADDING);
    PRINT("pkcs1_padding  result",result,len);
#endif

}