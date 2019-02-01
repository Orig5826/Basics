/**
 * @file crc.h
 * @author wenjf
 * @brief 
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#pragma once

#include <stdint.h>

#define CRC_CCIT_CUSTOM		-1
#define CRC_CCIT_KERMIT		0
#define CRC_CCIT_XMODEM		1
#define CRC_CCIT_X_25		4

void crc_ccit_setmode(uint8_t mode);
uint16_t crc_ccit_calc(const uint8_t *bytes, unsigned len);
// 
void crc_ccit_custom(uint16_t init, uint16_t xor, uint8_t reverse_in, uint8_t reverse_out);
