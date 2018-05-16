
#ifndef _DEMO_H_
#define _DEMO_H_

//------------------------------------------
//		register  driver 
#include "stm32f10x.h"
#include "typedef.h"
//------------------------------------------
//		register  driver 
#include "reg_gpio.h"
#include "reg_uart.h"
#include "reg_tim.h"
#include "reg_flash.h"

//------------------------------------------
//			demo
//		GPIO
void reg_gpio_delay(uint32_t n);
void gpio_demo(void);
//		UART
void uart1_demo(void);
void uart1_shell_demo(void);
//		TIM
void tim_wait_all_demo(void);
void tim_intr_demo(void);
//		FLASH
void flash_demo(void);

#endif
