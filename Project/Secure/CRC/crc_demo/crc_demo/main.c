/**
 * @file main.c
 * @author wenjf
 * @brief 
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include <stdio.h>
#include "crc.h"

void display_hex(uint8_t* data, uint32_t len)
{
	uint32_t i = 0;
	for (i = 0; i < len; i++)
	{
		printf("%02X ", *(data + i));
	}
	printf("\n");
}

void display_result(uint8_t mode, uint16_t result)
{
	printf("mode = %3d, crc_result = %04X\n", mode, result);
}

/*
* 测试数据示例
data:
31 32 33 34 35 36 37 38
------------------------------
mode =   0, crc_result = 8B19
mode =   1, crc_result = 9015
mode =   2, crc_result = A12B
mode =   3, crc_result = 5ED4
mode =   4, crc_result = 086A
mode =   5, crc_result = A12B
mode =   6, crc_result = 712C
mode =   7, crc_result = 8B6E
mode =   8, crc_result = D659
mode =   9, crc_result = DE23
----------
mode = 255, crc_result = 086A
*/
void main()
{
	uint32_t mode;
	uint16_t result;

	uint8_t data[] = "12345678";
	uint32_t length = sizeof(data) - 1;

	printf("data:\n");
	display_hex(data, length);
	printf("------------------------------\n");

	for (mode = 0; mode < CRC_MODE_END; mode++)
	{
		g_crc.init(mode, 0);

		// 单包直接计算
		// g_crc.update(data, length);

		// 分包计算
		g_crc.update(data, 1);
		g_crc.update(data + 1, 3);
		g_crc.update(data + 4, 4);

		result = g_crc.get_result();
		display_result(mode, result);
	}

	// 用自定义接口仿一下 CRC_CCIT_X_25
	printf("----------\n");
	g_crc.custom(0xffff, 0xffff, 1, 1);
	g_crc.init(CRC_CUSTOM, 0);
	g_crc.update(data, length);
	result = g_crc.get_result();
	display_result(CRC_CUSTOM, result);
}
