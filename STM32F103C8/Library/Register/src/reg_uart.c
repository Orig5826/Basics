
#include "reg_uart.h"

// 映射关系：
// PA9 -> TX   PA10 -> RX
void reg_uart_init(void)
{
	//GPIO时钟开启
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//配置速度
	GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_MODE10);
	GPIOA->CRH |= GPIO_CRH_MODE9_1 ;//| GPIO_CRH_MODE10_1;				//RX->Input,TX->OUT 2MHz
	//复用,推挽输出
	GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_CNF10);
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_0;//RX->Floating input, TX->AF_OUT Push-pull
	
	//AFIO 时钟开启
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN;
	//默认 PA9/PA10
	AFIO->MAPR &= ~AFIO_MAPR_USART1_REMAP;
	
	//串口时钟开启
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	//8 Data bits,无奇偶校验
	USART1->CR1 &= ~(USART_CR1_M | USART_CR1_PCE);
	//TE,RE
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
	//default: 1 Stop bit
	USART1->CR2 &= ~USART_CR2_STOP;
	//配置bps=115200,则72MHz，查表得39.0625
	USART1->BRR = 0x0270|0x0001;
	
	//开启串口
	USART1->CR1 |= USART_CR1_UE;
}

uint32_t reg_uart_sendstr(const uint8_t * str,uint32_t len)
{
	uint32_t i = 0;
	if(0 == len)
	{
		while(*(str+i) != '\0')
		{
			//发送一个字节
			while(!(USART1->SR & USART_SR_TXE));
			USART1->DR = *(str+i);
			i++;
		}
	}
	else
	{
		for(i = 0; i < len && *(str+i) != '\0'; i++)
		{
			//发送一个字节
			while(!(USART1->SR & USART_SR_TXE));
			USART1->DR = *(str+i);
		}
	}
	return i;
}

uint32_t reg_uart_sendhex(const uint8_t * str,uint32_t len)
{
	uint32_t i = 0;
	uint8_t temp = 0x00;
	while(i < len)
	{
		//发送一个字节
		temp = "0123456789ABCDEF"[(*(str+i) & 0xf0) >> 4];
		while(!(USART1->SR & USART_SR_TXE));
		USART1->DR = temp;
		
		temp = "0123456789ABCDEF"[(*(str+i) & 0x0f)];
		while(!(USART1->SR & USART_SR_TXE));
		USART1->DR = temp;
		
		while(!(USART1->SR & USART_SR_TXE));
		USART1->DR = 0x20;
		
		i++;
	}
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = '\r';
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = '\n';
	return i;
}


void reg_uart_sendbyte(const uint8_t data)
{
	//发送一个字节
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = data;
}

uint8_t reg_uart_recvbyte(void)
{
	uint8_t temp;
	
	while(!(USART1->SR & USART_SR_RXNE));
	temp = (uint8_t)USART1->DR;
	
	return temp;
}


