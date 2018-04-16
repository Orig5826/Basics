/* -----------------------------------------
	经过查看Data Sheet知道stm32f103c8t6
	仅仅支持
	TIM1/TIM8,TIM2~5
-----------------------------------------*/
#include "reg_tim.h"

// --------------------------------------
// 系统时钟SysClock = 72,000,000Hz的情况
void reg_tim2_init(void)
{
	//TIM2时钟开启
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 7200 - 1;		//0.1ms
	TIM2->ARR = 5000;			//0.5s
	//ARPE=1，UDIS=0，CEN=1，CNT_EN=1
	TIM2->CR1 = TIM_CR1_ARPE;		//reload
	TIM2->CR1 &= ~TIM_CR1_CMS;		//Edge-aligned mode
	TIM2->CR1 |= TIM_CR1_DIR;		//downcounter
	//配置
	//定时器使能
	TIM2->CR1 |= TIM_CR1_CEN; 
}
