
#ifndef _REG_GPIO_H_
#define _REG_GPIO_H_

#include "stm32f10x.h"

//stm32f10x
#define LED1_ON			(GPIOB->BRR = GPIO_BRR_BR8)
#define LED1_OFF		(GPIOB->BSRR = GPIO_BSRR_BS8)


// Interface
void reg_gpio_init(void);

#endif
