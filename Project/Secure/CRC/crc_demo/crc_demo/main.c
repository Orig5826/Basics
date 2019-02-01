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

void main()
{
#define SIZE 10
	// uint8_t data[SIZE] = "12345678";
	uint8_t data[SIZE] = "\x13\x1D\x11\x22\x33\x44\x55\x66\x77\x88";
	uint16_t crc_result = 0;

	crc_ccit_setmode(CRC_CCIT_KERMIT);
	crc_result = crc_ccit_calc(data, SIZE);
	printf("0x%04x\n", crc_result);

	crc_ccit_setmode(CRC_CCIT_XMODEM);
	crc_result = crc_ccit_calc(data, SIZE);
	printf("0x%04x\n", crc_result);

	crc_ccit_setmode(CRC_CCIT_X_25);
	crc_result = crc_ccit_calc(data, SIZE);
	printf("0x%04x\n", crc_result);
}
