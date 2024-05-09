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
//#define SPI_CS_EN()		GPIO_ResetBits(GPIOA,GPIO_Pin_4)
//#define SPI_CS_DN()		GPIO_SetBits(GPIOA,GPIO_Pin_4)

 #define SPI_CS_EN()     SPI_Cmd(SPI1,ENABLE)
 #define SPI_CS_DN()     SPI_Cmd(SPI1,DISABLE)

//#define SPI_CS_EN()       SPI_SSOutputCmd(SPI1, ENABLE)
//#define SPI_CS_DN()       SPI_SSOutputCmd(SPI1, DISABLE)


void SPI_Example(void);

#endif

