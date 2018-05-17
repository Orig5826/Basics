
#include "demo.h"

uint8_t flip_flag = 0;
void tim_intr_demo(void)
{
	reg_gpio_init();
	reg_tim2_init();
	reg_time2_intr_init();
	while(1)
	{
		if(0 != flip_flag)
		{
			flip_flag = 0;
			LED1_FLIP;
		}
		reg_gpio_delay(50);
	}
}

//中断处理
void TIM2_IRQHandler(void)
{
	//关闭定时器中断
	TIM2->DIER &= ~TIM_DIER_TIE;
	//清中断标志
	if (TIM2->SR & TIM_SR_TIF)
	{
		TIM2->SR |= TIM_SR_TIF;
		
		//中断中进行的操作
		flip_flag = 1;
	}
	//重新开启定时器中断
	TIM2->DIER |= TIM_DIER_TIE;
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
