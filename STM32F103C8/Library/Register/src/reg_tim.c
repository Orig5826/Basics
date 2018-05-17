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

// --------------------------------------
// Time2中断配置
#define NVIC_ADDR	0x08000000		//Flash Addr
#define NVIV_OFFSET	0x0000			//偏移 = 0x200 * N
void reg_time2_intr_init(void)
{
	//配置中断向量表,Flash
	SCB->VTOR = NVIC_ADDR | (NVIV_OFFSET & (uint32_t)0x1FFFFF80);
	// 配置中断优先级,注意STM32用的是高4bit
	// 配置抢占式优先级和响应式优先级各自占2bit
	SCB->AIRCR = 0x05FA0500;
	// 配置抢占式中段级别为2，响应式中断级别为2
	//NVIC->IP[TIM2_IRQn] |= 0xa0;
	//使能中断
	//NVIC->ISER[TIM2_IRQn/8] |= 1 << (TIM2_IRQn%8);

	NVIC->IP[28] |= 0xa0;
	//使能中断
	NVIC->ISER[3] |= 1 << 5;
	NVIC->IABR[3] |= 1 << 5;
	
	//开启TIM2中断
	TIM2->DIER |= TIM_DIER_TIE;
}
