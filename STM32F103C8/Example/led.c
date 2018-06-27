#include "led.h"
#include "stm32f10x_conf.h"

void LED_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	/* GPIOD Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_8;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOB,&gpio);
}
