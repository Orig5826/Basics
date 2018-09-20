/**
 * @brief des 算法Demo示例
 * 
 * @file des_demo.c
 * @author wenjf
 * @date 2018-09-20
 */

#include "alg_demo.h"
#include <openssl/des.h>

#define DES_BLOCK_SIZE  0x08

void des_demo(void)
{
    DES_cblock key;
    DES_key_schedule key_schedule;
    const uint8_t key_len = sizeof(key);
#define DATA_SIZE 64
#if DATA_SIZE % DES_BLOCK_SIZE != 0
#error "DATA_SIZE is not correct!"
#endif
    uint8_t data[DATA_SIZE];
    uint32_t i = 0;

    DES_random_key(&key);
    PRINT("key", key, key_len);
    for (i = 0; i < DATA_SIZE; i++)
    {
        data[i] = i;
    }
    PRINT("data",data,DATA_SIZE);
    // 配置KEY
    DES_set_key(&key,&key_schedule);
    //DES_set_key_checked(&key,&key_schedule);    //奇偶校验和弱KEY判断
    //DES_set_key_unchecked(&key,&key_schedule);  //没有...

    /* 加密 */
    for(i = 0; i < DATA_SIZE; i+= DES_BLOCK_SIZE)
    {
        DES_ecb_encrypt((const_DES_cblock *)(data + i),(DES_cblock *)(data + i),&key_schedule,DES_ENCRYPT);
    }
    PRINT("cipher",data,DATA_SIZE);

    /* 解密 */
    for(i = 0; i < DATA_SIZE; i+= DES_BLOCK_SIZE)
    {
        DES_ecb_encrypt((const_DES_cblock *)(data + i),(DES_cblock *)(data + i),&key_schedule,DES_DECRYPT);
    }
    PRINT("result",data,DATA_SIZE);
}

void des_cbc_demo(void)
{
    DES_cblock key;
    DES_cblock iv = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
    DES_key_schedule key_schedule;
    const uint8_t key_len = sizeof(key);
#undef DATA_SIZE
#define DATA_SIZE 64
#if DATA_SIZE % DES_BLOCK_SIZE != 0
#error "DATA_SIZE is not correct!"
#endif
    uint8_t data[DATA_SIZE];    //保证足够密文数据的存放
    uint32_t i = 0;

    DES_random_key(&key);
    PRINT("key", key, key_len);
    for (i = 0; i < DATA_SIZE; i++)
    {
        data[i] = i;
    }
    PRINT("data",data,DATA_SIZE);
    // 配置KEY
    DES_set_key(&key,&key_schedule);
    //DES_set_key_checked(&key,&key_schedule);    //奇偶校验和弱KEY判断
    //DES_set_key_unchecked(&key,&key_schedule);  //没有...

    /* @breaf DES_CBC 加密 
     *
     * @param
     *      @in 
     *      @out 8的整数倍
     */
    DES_cbc_encrypt(data,data,DATA_SIZE,&key_schedule,&iv,DES_ENCRYPT);
    PRINT("cipher",data,DATA_SIZE);

    /* DES_CBC 解密 */
    DES_cbc_encrypt(data,data,DATA_SIZE,&key_schedule,&iv,DES_DECRYPT);
    PRINT("result",data,DATA_SIZE);
}