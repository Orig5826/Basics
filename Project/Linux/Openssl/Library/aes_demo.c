/*
 * @breaf aes demo
 *     
 */
#include "alg_demo.h"
#include <openssl/aes.h>

/*
 * @breaf aes_demo
 *     The length of data must be an integer multiple of 16
 */
void aes_demo(void)
{
    const uint8_t key[16 + 8 + 8] = {
        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
        0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,    //aes 128
        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,    //aes 192
        0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,    //aes 256
    };
    // bits: 128/192/256
    const uint32_t key_bits = 128;
#define DATA_SIZE       64
#if DATA_SIZE % 16 != 0
#error "DATA_SIZE is not correct!"
#endif
    uint8_t data[DATA_SIZE];
    uint32_t i = 0;

    AES_KEY aes_key;

    // data initial
    for(i = 0; i < DATA_SIZE; i ++)
    {
        data[i] = i;
    }
    printf("data:\n");
    display(data,DATA_SIZE);

    /*
        * @breaf set the encrypt key
        * @param
        *    @arg key 16/24/32 Bytes
        *    @arg bits: 128/192/256
        * @ret 0.succeed
    */
    AES_set_encrypt_key(key,key_bits,&aes_key);

    /*
    * @breaf encrypt
    * @param
    *    @arg in 16 Bytes
    *    @arg out: 16 Bytes
    * @ret 0.succeed
    */
    for(i = 0; i < DATA_SIZE; i+=16)
    {
        AES_encrypt(data + i,data + i,&aes_key);
        //AES_ecb_encrypt(data + i,data + i,&aes_key,AES_ENCRYPT);
    }
    printf("cipher:\n");
    display(data,DATA_SIZE);

    // [notes] You have to set the key again
    // set the decrypt key
    AES_set_decrypt_key(key,key_bits,&aes_key);
    // dectypt  [notes] same as AES_encrypt
    for(i = 0; i < DATA_SIZE; i+=16)
    {
        AES_decrypt(data + i,data + i,&aes_key);
        //AES_ecb_encrypt(data + i,data + i,&aes_key,AES_DECRYPT);
    }

    printf("result:\n");
    display(data,DATA_SIZE);
}

/*
 * @breaf aes_demo2
 *     There is no limit to the length of data, but the output cache
 *  needs to be sufficient to accommodate ciphertext. 
 */
void aes_cbc_demo(void)
{
    const uint8_t key[16 + 8 + 8] = {
        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
        0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,
        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
        0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,
    };
    const uint32_t key_bits = 256;
#undef DATA_SIZE
#define DATA_SIZE       64
    uint8_t data[DATA_SIZE];
    uint8_t cipher[DATA_SIZE + 16]; // +16: Ensure cache is large enough. 
    uint8_t result[DATA_SIZE];
    uint32_t i = 0;

    AES_KEY aes_key;

    // data initial
    memset(cipher,0x00,DATA_SIZE + 16);
    memset(result,0x00,DATA_SIZE);
    for(i = 0; i < DATA_SIZE; i ++)
    {
        data[i] = i;
    }
    printf("data:\n");
    display(data,DATA_SIZE);

    /*
        * @breaf set the encrypt key
        * @param
        *    @arg key 16/24/32 Bytes
        *    @arg bits: 128/192/256
        * @ret 0.succeed
    */
    AES_set_encrypt_key(key,key_bits,&aes_key);
    /*
        * @breaf encrypt
        * @param
    */
    AES_ecb_encrypt(data,cipher,&aes_key,AES_ENCRYPT);


    // [notes] You have to set the key again
    // set the decrypt key
    AES_set_decrypt_key(key,key_bits,&aes_key);
    // dectypt  [notes] same as AES_encrypt
    AES_ecb_encrypt(cipher,result,&aes_key,AES_DECRYPT);

    printf("cipher:\n");
    display(cipher,DATA_SIZE);
    printf("result:\n");
    display(result,DATA_SIZE);
}
