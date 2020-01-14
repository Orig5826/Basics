
#include "i2c_slave.h"
#include "led.h"

// I2C接口
#define I2Cx						I2C1

void i2c_slave_init(uint8_t addr)
{
	I2C_InitTypeDef  i2c_config;
	GPIO_InitTypeDef  gpio_config;
	
	//---------------------------------------
	//	打开I2C时钟
	//---------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,    ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,     ENABLE);

	//-----------------------------------------
	//	I2C初始化
	//-----------------------------------------
	gpio_config.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	gpio_config.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_config.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &gpio_config);
	
	I2C_DeInit(I2Cx);
	
	i2c_config.I2C_Mode = I2C_Mode_I2C;
	i2c_config.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c_config.I2C_OwnAddress1 = addr;
	i2c_config.I2C_Ack = I2C_Ack_Enable;
	i2c_config.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c_config.I2C_ClockSpeed = 100000;
	I2C_Cmd(I2Cx, ENABLE);
	I2C_Init(I2Cx, &i2c_config);
	// -----------------------------------
	// 使能I2C应答
	// -----------------------------------
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}


void i2c_slave_send(uint8_t * data, uint32_t len)
{
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	//-------------------------------------
	// 等待地址匹配
	//-------------------------------------
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED));
	
	//-------------------------------------
	//	发送数据
	//-------------------------------------
	for(uint32_t i = 0; i < len; i++)
	{
		LED_ON();
		LED2_ON();
		
		I2C_SendData(I2Cx, *(data + i));
		if(i < len - 1)
		{
			while(!I2C_CheckEvent(I2Cx, I2C_EVENT_SLAVE_BYTE_TRANSMITTED));
			LED2_OFF();
		}
		else
		{
			//-------------------------------------
			// 等待NAK
			//-------------------------------------
			while(!I2C_CheckEvent(I2Cx, I2C_EVENT_SLAVE_ACK_FAILURE));
			LED_OFF();
			I2Cx->SR1 &= ~0x400;
		}
		
		#if 0
		if(I2Cx->SR1 & 0x04)
		{
			LED2_OFF();
		}

		if((I2Cx->SR1 & 0x400))
		{
			LED_OFF();
			I2Cx->SR1 &= ~0x400;
		}
		#endif
	}
}

void i2c_slave_recv(uint8_t * data, uint32_t len)
{
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	//-------------------------------------
	// 等待地址匹配
	//-------------------------------------
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED));

	//-------------------------------------
	//	发送数据
	//-------------------------------------
	for(uint32_t i = 0; i < len; i++)
	{
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_SLAVE_BYTE_RECEIVED));
		*(data + i) = I2C_ReceiveData(I2Cx);
	}

	//-------------------------------------
	// 等待STOP
	//-------------------------------------
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_SLAVE_STOP_DETECTED));
}


void i2c_slave_example(void)
{
	uint8_t rbuf[128] = {0};
	uint8_t sbuf[128] = {0};
	uint32_t len = 10;
	uint32_t i = 0;

	LED_Init();
	LED_OFF();
	
	// stm32的i2c配置的地址，包括读写bit
	// 将该bit置为0即可
	i2c_slave_init(0x50);
	
	while(1)
	{
		i2c_slave_recv(rbuf,len);

		for(i = 0; i < len; i++)
		{
			sbuf[i] = rbuf[i] + 0x30;
		}
		i2c_slave_send(sbuf,len);
	}
}

