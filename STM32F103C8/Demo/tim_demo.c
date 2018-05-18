
#include "demo.h"

uint8_t flip_flag = 0;
void tim_intr_demo(void)
{
	reg_gpio_init();
	reg_uart_init();

	//----------------------------------
	// 感觉配置没问题，Debug的时候手动配置UIF，可以进入中断。
	// 但程序自己运行，硬件中断挂起感觉一直没有作用。
	// 后来调整了一下顺序，先配置tim，再开启中断。成功！！！
	//----------------------------------
	reg_tim2_init();
	reg_time2_intr_init();
	
	reg_uart_sendstr("tim2 init finished!\r\n",0);
	while(1)
	{
		if(0 != flip_flag)
		{
			flip_flag = 0;
			reg_uart_sendstr("tim2 irq_handle!\r\n",0);
		}
	}
}

#ifdef _REG_INTR_DEMO_
//中断处理
void TIM2_IRQHandler(void)
{
	// -------------------------------------
	// 这里之所以不能按照预期产生闪烁效果
	// 我认为是该中断函数的进入不仅仅有TIM_SR_UIF中断
	// 还有其他情况下的中断我没有考虑到。
	// 因此在处理各种不同功能的时候，要先判断其中断标志
	// 然后再进行相应的操作
	// --------------------------------------
	// LED1_FLIP;
	if (TIM2->SR & TIM_SR_UIF)
	{
		flip_flag = 1;

		LED1_FLIP;

		//清除相应的中断标识	
		TIM2->SR &= ~TIM_SR_UIF;
	}
}
#endif

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
