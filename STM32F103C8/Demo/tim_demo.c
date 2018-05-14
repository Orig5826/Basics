
#include "demo.h"

void tim_intr_demo(void)
{
	reg_gpio_init();
	
	while(1)
	{

	}
}

void tim_wait_all_demo(void)
{
	static BOOL bright = FALSE;
	reg_gpio_init();
	reg_tim2_init();
	while(1)
	{
		while(!(TIM2->SR & TIM_SR_UIF));
		TIM2->SR &= ~TIM_SR_UIF;
		if(TRUE != bright)
		{
			bright = TRUE;
			LED1_OFF;
		}
		else
		{
			bright = FALSE;
			LED1_ON;
		}
	}
}
