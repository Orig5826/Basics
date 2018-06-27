
#include "demo.h"

// ---------------------------------------
// 72MHz 系统时钟
// n=1 大约0.01s
void reg_gpio_delay(volatile uint32_t n)
{
	volatile uint32_t i;
	while(n--)
	{
		i = 0x0000C000;
		while(i--);
	}
}

void gpio_demo(void)
{
	uint32_t i = 0;
	reg_gpio_init();
	while(1)
	{
		LED1_OFF;
		reg_gpio_delay(100);
		LED1_ON;
		reg_gpio_delay(100);
		
		LED1_OFF;
		reg_gpio_delay(50);
		for(i = 0; i < 10; i++)
		{
			reg_gpio_delay(5);
			LED1_ON;
			reg_gpio_delay(5);
			LED1_OFF;
		}
	}
}
