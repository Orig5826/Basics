
#ifndef _DEMO_H_
#define _DEMO_H_

//------------------------------------------
//		register  driver 
#include "stm32f10x.h"

typedef enum _BOOL
{
	FALSE = 0,
	TRUE
}BOOL;

#if 0
typedef uint8_t 			BOOL;
#ifndef TRUE
#define TRUE				1
#endif
#ifndef FALSE
#define FALSE				0
#endif
#endif

//------------------------------------------
//		register  driver 
#include "reg_gpio.h"
#include "reg_uart.h"
#include "reg_tim.h"

//------------------------------------------
//			demo
//		GPIO
void reg_gpio_delay(uint32_t n);
void gpio_demo(void);
//		UART
void uart1_demo(void);
//		TIM
void tim_wait_all_demo(void);
void tim_intr_demo(void);

#endif
