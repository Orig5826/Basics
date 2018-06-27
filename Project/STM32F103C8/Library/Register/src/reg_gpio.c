
#include "reg_gpio.h"

// LED1 ->  PB8
void reg_gpio_init(void)
{
	//GPIO时钟开启
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	//配置输出，速度
	GPIOB->CRH &= ~GPIO_CRH_MODE8;
	GPIOB->CRH |= GPIO_CRH_MODE8_1;		//2MHz
	//推挽输出
	GPIOB->CRH &= ~GPIO_CRH_CNF8;
	
	//初始配置为1
	GPIOB->ODR |= GPIO_ODR_ODR8;
}
