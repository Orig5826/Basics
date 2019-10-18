/**
 * @brief 
 * 
 * @file spi.h
 * @author wenjf
 * @date 2019-10-17
 */
#ifndef _SPI_H_
#define _SPI_H_

/*------------------------------------------------
 				1.	头文件
------------------------------------------------*/
#include "stm32f10x_conf.h"

// 使能
#define SPI_CS_EN()		GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define SPI_CS_DN()		GPIO_ResetBits(GPIOA,GPIO_Pin_4)

void SPI_Example(void);

#endif

