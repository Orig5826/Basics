#include "uart.h"

void UartInit(void)
{
	USART_InitTypeDef uartConfig;

	//----------------------------------------
	// 先配置好需要使用的UART1相应的引脚
	// 并使能串口时钟
	//----------------------------------------
	GPIO_InitTypeDef gpioConfig;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	//TX
	gpioConfig.GPIO_Pin = GPIO_Pin_9;
	gpioConfig.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioConfig.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioConfig);
	//RX
	gpioConfig.GPIO_Pin = GPIO_Pin_10;
	gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpioConfig);

	//----------------------------------------
	// 再配置UART1相应功能
	//----------------------------------------
	// 1.串口配置
	USART_StructInit(&uartConfig);
	uartConfig.USART_BaudRate = 115200;
	USART_Init(USART1, &uartConfig);

	// 2.使能UART
	USART_Cmd(USART1, ENABLE);
}

void UartSendString(const uint8_t *str, uint32_t strlen)

{
	uint32_t i = 0;
	if (strlen == 0)
	{
		for (i = 0; *str != '\0'; i++)
		{
			USART_SendData(USART1, *str);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
				; //等待数据发送完
			str++;
		}
	}
	else
	{
		for (i = 0; i < strlen; i++)
		{
			USART_SendData(USART1, *str);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
				; //等待数据发送完
			str++;
		}
	}
}

void UART_SendHex(const uint8_t *str, uint32_t strlen)
{
	uint32_t i = 0;
	uint8_t temp = 0x00;

	for (i = 0; i < strlen; i++)
	{
		temp = "0123456789ABCDEF"[(*(str + i) >> 4) & 0x0f];
		USART_SendData(USART1, temp);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
			; //等待数据发送完

		temp = "0123456789ABCDEF"[*(str + i) & 0x0f];
		USART_SendData(USART1, temp);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
			; //等待数据发送完

		temp = 0x20;
		USART_SendData(USART1, temp);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
			; //等待数据发送完
	}

	temp = '\r';
	USART_SendData(USART1, temp);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
		; //等待数据发送完
	temp = '\n';
	USART_SendData(USART1, temp);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
		; //等待数据发送完
}
