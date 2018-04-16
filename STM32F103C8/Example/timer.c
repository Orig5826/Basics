#include "stm32f10x_conf.h"

void TimerInit(void)
{
	TIM_TimeBaseInitTypeDef timerConfig;
	// 0.使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	// 1.定时器基础配置
	TIM_TimeBaseStructInit(&timerConfig);
	timerConfig.TIM_Period = 5000 - 1;					//因此一个计数代表着0.1ms
	timerConfig.TIM_Prescaler = 7200;					//CoreClock is 72000000 = 72MHz
	timerConfig.TIM_CounterMode = TIM_CounterMode_Up;	//注意：无论向上或者向下计数，范围都是 0-自动加载值
	
	TIM_TimeBaseInit(TIM2,&timerConfig);
	
	//2. 中断配置
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    // 定时器中断使能

	//3. 使能定时器
	TIM_Cmd(TIM2,ENABLE);						// 开启定时器
}

//定时器中断配置
void TimerNVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


uint8_t sendflag = 0;
void Timer_Example(void)
{
	LED_Init();
	LED_OFF; 

	UartInit();
	UartSendString("uart ok!\r\n",10);
	
	TimerInit();
	TimerNVIC_Config();
	while(1)
	{
		if(1 == sendflag)
		{
			UartSendString("uart ok!\r\n",10);
			sendflag = 0;
		}
	}
}

