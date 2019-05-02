
#include "demo.h"
#include <string.h>

volatile uint8_t led_mode;

#ifdef _REG_UART2_SHELL_DEMO_
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
		//清除相应的中断标识	
		TIM2->SR &= ~TIM_SR_UIF;

		switch(led_mode)
		{
			case 0:
			{
				LED1_OFF;
			}break;
			case 1:
			{
				LED1_ON;
			}break;
			case 2:
			{
				//翻转电平
				LED1_FLIP;
			}break;
		}
	}
}
#endif

void uart1_demo(void)
{
	uint8_t sBuf[9] = "\x1f\x2e\x3d\x4c\x5b\x6a\x79\x80";
	reg_uart_init();
	while(1)
	{
		reg_gpio_delay(100);
		if(10 != reg_uart_sendstr((const uint8_t *)"UART OK!\r\n",12))
		{
			reg_uart_sendstr((const uint8_t *)"retLen != needLen!\r\n",0);
		}
		reg_uart_sendhex(sBuf,8);
	}
}

#define RBUF_SIZE	0x400
void uart1_shell_demo(void)
{
	static uint8_t tabLen = 8;	//默认tab长度等价于8个space
	uint8_t rBuf[RBUF_SIZE];
	uint32_t rLen = 0;
	uint8_t temp = 0x55;
	uint32_t i = 0;

	led_mode = 0;
	reg_gpio_init();
	reg_uart_init();
	reg_uart_sendstr((const uint8_t *)"uart1_shell_demo\r\n",0);

	reg_tim2_init();
	reg_time2_intr_init();
	
	//刚刚开始 起始2字符头
	reg_uart_sendbyte('>');
	reg_uart_sendbyte(' ');
	while(1)
	{
		temp = reg_uart_recvbyte();
		if(temp == '\b')
		{
			if(rLen > 0)
			{
				reg_uart_sendbyte('\b');
				reg_uart_sendbyte(' ');
				reg_uart_sendbyte('\b');
				rLen --;
			}
		}
		else if(temp == '\r')
		{
			reg_uart_sendbyte('\r');
			reg_uart_sendbyte('\n');
			
			//-----------------------------
			// 接收到数据之后，再做处理判断
			//-----------------------------
			rBuf[rLen] = '\0';
			if(0 == strcmp((const char *)rBuf,"led on"))
			{
				reg_uart_sendstr((uint8_t *)"[Succeed] Led ON !\r\n",0);
				led_mode = 1;
			}
			else if(0 == strcmp((const char *)rBuf,"led off"))
			{
				reg_uart_sendstr((uint8_t *)"[Succeed] Led OFF !\r\n",0);
				led_mode = 0;
			}
			else if(0 == strcmp((const char *)rBuf,"led flip"))
			{
				reg_uart_sendstr((uint8_t *)"[Succeed] Led Flip !\r\n",0);
				led_mode = 2;
			}
			else
			{
				if(rLen != 0)
				{
					reg_uart_sendstr((uint8_t *)"[Error] unknow command!\r\n",0);
				}
			}
			//-----------------------------
			// 数据处理完毕之后，清空buf
			//-----------------------------
			rLen = 0;
			//新一轮开始
			reg_uart_sendbyte('>');
			reg_uart_sendbyte(' ');
		}
		else if(temp == '\t')
		{
			unsigned char taboffset = 0;
			taboffset = tabLen - (2+rLen)%tabLen;
			for(i = 0; i < taboffset; i++)
			{
				rBuf[rLen] = ' ';		//把tab当成空格存储
				reg_uart_sendbyte(' '); //返回也返回空格
			}
			rLen += taboffset;
		}
		else if(temp >= 0x20 && temp <= 0x7F)
		{
			reg_uart_sendbyte(temp);
			rBuf[rLen] = temp;
			rLen++;
		}
		else
		{
			#if 0
			//调试信息
			reg_uart_sendbyte('\\');
			reg_uart_sendbyte('x');
			reg_uart_sendbyte("0123456789ABCDEF"[(temp>>4) & 0x0f]);
			reg_uart_sendbyte("0123456789ABCDEF"[temp & 0x0f]);
			#endif
		}

		#if 0
		switch(led_mode)
		{
			case 0:
			{
				LED1_OFF;
			}break;
			case 1:
			{
				LED1_ON;
			}break;
			case 2:
			{
				//翻转电平
				LED1_FLIP;
			}break;
		}
		#endif
	}
}
