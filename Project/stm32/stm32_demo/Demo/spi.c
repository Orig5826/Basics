/**
 * @file spi.c
 * @author wenjf
 * @brief stm32 spi通讯示例
 * @version 0.1
 * @date 2019-10-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "spi.h"
#include <string.h>

/**
 * @brief SPI初始化配置
 * 
 */
void SPI_Init_Config(void)
{
	GPIO_InitTypeDef gpio_config;
	SPI_InitTypeDef  spi_config;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1,  ENABLE );

	// ----------------------------------
	// SPI1_CS -> PA4 (此处单独配置)
	// SPI1_SCK -> PA5
	// SPI1_MISO -> PA6
	// SPI1_MOSI -> PA7
	// ----------------------------------
	gpio_config.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio_config.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_config);

	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

	// ----------------------------------
	// PA4 -> CS
	// ----------------------------------
	gpio_config.GPIO_Pin = GPIO_Pin_4;
	gpio_config.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_config);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	// SPI 外设配置
	spi_config.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	spi_config.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	spi_config.SPI_DataSize = SPI_DataSize_8b;	//设置SPI的数据大小:SPI发送接收8位帧结构
	spi_config.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为低电平
	spi_config.SPI_CPHA = SPI_CPHA_2Edge;		//串行同步时钟的第2个跳变沿（上升或下降）数据被采样
	spi_config.SPI_NSS = SPI_NSS_Soft;			//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	spi_config.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;	//定义波特率预分频的值:波特率预分频值为64
	spi_config.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	spi_config.SPI_CRCPolynomial = 7;			//CRC值计算的多项式
	SPI_Init(SPI1, &spi_config); 				//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

	// SPI 使能
	SPI_Cmd(SPI1, ENABLE);
}

/**
 * @brief SPI1 接口发送
 * 
 * @param sbuf 待发送的数据
 * @param slen 待发送的数据长度
 * @return 0.发送超时 1.发送成功
 * 
 * @notes 根据从设备数据收发情况进行相应的代码修改
 */
u8 SPI1_Send(u8 * sbuf, u32 slen)
{
	u32 i = 0;
	u32 retry = 0;

	SPI_CS_DN();
	for(i = 0; i < slen; i++)
	{
		retry = 0;
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //0：发送缓冲非空,等待发送缓冲器变空
		{
			retry++;
			if(retry > 500)
			{
				return 0;
			}
		}
		SPI_I2S_SendData(SPI1, sbuf[i]);
	}

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
		;
	
	SPI_CS_EN();
	return 1;
}

/**
 * @brief SPI1 数据接收
 * 
 * @param rbuf 数据接收缓存
 * @param rlen 接收到的数据长度
 * @return u8 0.发送超时 1.发送成功
 */
u8 SPI1_Recv(u8 * rbuf, u32 rlen)
{
	u32 i = 0;
	u32 retry = 0;

	// ------------------------------------------
	// 将数据接收前的第一个字节舍弃，因为是
	// 上一次发来的最后一个字节，还在移位寄存器中
	// 正点原子的处理方式是针对该问题么？
	// 初始先发一个字节FF
	// 随后一发一收，当然了也需要从设备配合
	// ------------------------------------------
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;
	SPI_I2S_ReceiveData(SPI1);


	SPI_CS_DN();
	for(i = 0; i < rlen; i++)
	{
		retry = 0;
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //0：发送缓冲非空,等待发送缓冲器变空
		{
			retry++;
			if(retry > 500)
			{
				return 0;
			}
		}
		SPI_I2S_SendData(SPI1, 0x00);
		
		retry = 0;
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//等待接收数据完成
		{
			retry++;
			if(retry > 500)
			{
				return 0;
			}
		}
		rbuf[i] = SPI_I2S_ReceiveData(SPI1); //返回最近接收的数据，SPI_DR寄存器里面的
	}
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
		;
	
	SPI_CS_EN();
	return 1;
}

/**
 * @brief 简单延时函数
 * 
 * @param n 1大约1ms左右 @默认时钟配置
 */
static void Delay(u32 n)
{
	volatile u32 m;
	while(n--)
	{
		m = 0x00002000;
		while(m--)
			;
	}
}


#define BUFFER_SIZE		1024
static uint8_t sbuf[BUFFER_SIZE];
static uint8_t rbuf[BUFFER_SIZE];

/**
 * @brief SPI通讯示例
 * 
 */
void SPI_Example(void)
{
	uint32_t i = 0;
	uint8_t blink = 0;
	LED_Init();
	SPI_Init_Config();
	
	LED_ON();
	Delay(3000);
	for(i = 0; i < BUFFER_SIZE; i++)
	{
		sbuf[i] = i & 0xff;
	}
	memset(rbuf,0x00,BUFFER_SIZE);
	LED_OFF();
	Delay(1000);
	
	while(1)
	{
		SPI1_Send(sbuf,BUFFER_SIZE);
		Delay(10);
		SPI1_Recv(rbuf,BUFFER_SIZE);
		
		for(i = 0; i < BUFFER_SIZE; i++)
		{
			if(sbuf[i] != rbuf[i])
			{
				// 出错 -> 快闪烁
				while(1)
				{
					// 正确 -> 慢闪烁
					if(blink == 0)
					{
						blink = 1;
						LED_ON();
					}
					else
					{
						blink = 0;
						LED_OFF();
					}
					Delay(100);
				}
			}
		}
		
		// 正确 -> 慢闪烁
		if(blink == 0)
		{
			blink = 1;
			LED_ON();
		}
		else
		{
			blink = 0;
			LED_OFF();
		}
		Delay(1000);
	}
}
