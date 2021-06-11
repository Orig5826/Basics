# CRC 算法示例——C语言
`2021.04.16 create by jianfeng`

相关协议

| 协议(poly = 1021)  | mode值  |
| :----------------: | --------|
| CRC_CCIT_KERMIT    | = 0,    |
| CRC_CCIT_XMODEM    | = 1,    |
| CRC_CCIT_FALSE     | = 2,    |
| CRC_CCIT_GENIBUS   | = 3,    |
| CRC_CCIT_X_25      | = 4,    |
| CRC_CCIT_MCRF4XX   | = 5,    |
| CRC_CCIT_AUG_CCIT  | = 6,    |
| CRC_CCIT_TMS37157  | = 7,    |
| CRC_CCIT_RIELLO    | = 8,    |
| CRC_CCIT_CRC_A     | = 9,    |

## API

直接调用g_crc的相关成员函数即可

```c
typedef struct _crc_t
{
    /**
     * @brief 0. 自定义参数
     *
     * @param init 初值
     * @param xor 结果异或值
     * @param reverse_in 输入数据是否需要按位翻转
     * @param reverse_out 输出数据是否需要按位翻转
     */
    void (*custom)(uint16_t init, uint16_t xor, uint8_t reverse_in, uint8_t reverse_out);

    /**
     * @brief 1. 初始化
     *     若自定义参数，则需要先执行**_custom函数
     * @param mode 模式（宏定义CRC_CCIT_xx）
     * @param endian 结果大小端
     * @return uint8_t 状态（宏定义CRC_ST_xx）
     */
    uint8_t(*init)(uint8_t mode, uint8_t endian);

    /**
     * @brief 2. 更新数据（可连续）
     *
     * @param bytes 数据内容
     * @param len 数据长度
     * @return uint8_t 状态（宏定义CRC_ST_xx）
     */
    uint8_t(*update)(uint8_t* data, uint32_t len);

    /**
     * @brief 3. 取CRC结果
     *
     * @return uint16_t
     */
    uint16_t(*get_result)(void);
}crc_t;

extern crc_t g_crc;
```

