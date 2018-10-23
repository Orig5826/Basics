/**
 * @brief 
 * 
 * @file i2c.h
 * @author wenjf
 * @date 2018-10-23
 */
#ifndef _I2C_HARD_H_
#define _I2C_HARD_H_

/*------------------------------------------------
 				1.	头文件
------------------------------------------------*/
#include "stm32f10x_conf.h"

void I2C_Init_Config(void);
void I2C_Write(u8* pBuffer,u16 len);
void I2C_Read(u8* pBuffer , u16 *len);

void I2C_Hard_Example(void);
/**********************************
			I2C总线
**********************************/
#endif
