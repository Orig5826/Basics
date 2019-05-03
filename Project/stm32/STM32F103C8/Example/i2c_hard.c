/**
 * @brief I2C Ӳ���ӿ�
 * 
 * @file i2c_hard.c
 * @author 
 * @modify wenjf
 * @date 2018-10-23
 */
#include "i2c_hard.h"
#include <string.h>

// ���һЩ���������û�а취ֱ�ӷ���2�ֽڳ����ֶε�����
// #define I2C_RECV_MODE2

//--------------------------------------------------
//	I2C �ӿ�����
//--------------------------------------------------
#define I2Cx						I2C1
#define SLAVE_ADDR					(0x10)
//��д��ַ
#define I2C_WRITE_ADDR				(SLAVE_ADDR << 1)
#define I2C_READ_ADDR				(SLAVE_ADDR << 1 | 0x01)

void I2C_Init_Config(void)
{
	I2C_InitTypeDef  i2c_config;
	GPIO_InitTypeDef  gpio_config;
	
	//---------------------------------------
	//	��I2Cʱ��
	//---------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,    ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,     ENABLE);

	//-----------------------------------------
	//	I2C��ʼ��
	//-----------------------------------------
	gpio_config.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	gpio_config.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_config.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &gpio_config);
	
	i2c_config.I2C_Mode = I2C_Mode_I2C;
	i2c_config.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c_config.I2C_OwnAddress1 = 0x00;
	i2c_config.I2C_Ack = I2C_Ack_Enable;
	i2c_config.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c_config.I2C_ClockSpeed = 100000;
	I2C_Cmd(I2Cx, ENABLE);
	I2C_Init(I2Cx, &i2c_config);
	// -----------------------------------
	// ʹ��I2CӦ��
	// -----------------------------------
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}

//--------------------------------------------------
//	I2C ����д��
//--------------------------------------------------
void I2C_Write(u8* sBuf,u16 sLen)
{
	if((0x00 == sLen) || (NULL == sBuf))
	{
		return;
	}
	
	//------------------------------------
	//	START
	//------------------------------------
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	//------------------------------------
	//	����д��ַ
	//------------------------------------
	I2C_Send7bitAddress(I2Cx, I2C_WRITE_ADDR, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	//-------------------------------------
	//	��������
	//-------------------------------------
	while(sLen)
	{
		I2C_SendData(I2Cx, *sBuf);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		sBuf++; 
		sLen--;       
	}
	//-------------------------------
	//	STOP
	//-------------------------------
	I2C_GenerateSTOP(I2Cx, ENABLE);
}


//--------------------------------------------------
//	I2C ���ݶ�ȡ
//--------------------------------------------------
void I2C_Read(u8* rBuf , u16 *rLen)
{
	u16 rev_len=0;
	u8* pTmpBuf = rBuf;

	if((0x00 == rLen) || (NULL == rBuf))
	{
	    return;
	}
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
		;
    I2C_AcknowledgeConfig(I2Cx, ENABLE);
	//----------------------------------------
	//	START
	//----------------------------------------
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	
	//----------------------------------------
	//	���Ͷ���ַ
	//----------------------------------------
	I2C_Send7bitAddress(I2Cx, I2C_READ_ADDR, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	//----------------------------------------
	//	�Ƚ����������ݵĳ��Ƚ��չ���(2 Bytes)
	//----------------------------------------
	rev_len = 2;
	while(rev_len)
	{
#ifdef I2C_RECV_MODE2
		if(rev_len == 1)
		{
			I2C_AcknowledgeConfig(I2Cx, DISABLE); 
		}
#endif		
	    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); 
	    *pTmpBuf = I2C_ReceiveData(I2Cx);
	    pTmpBuf++; 
	    rev_len--;       
	}
	rev_len = rBuf[0]*256 + rBuf[1] + 1;

	*rLen = rev_len + 2;

#ifdef I2C_RECV_MODE2
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	//----------------------------------------
	//	START
	//----------------------------------------
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	//----------------------------------------
	//	���Ͷ���ַ
	//----------------------------------------
	I2C_Send7bitAddress(I2Cx, I2C_READ_ADDR, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
#endif

	while(rev_len)
	{
	    if(rev_len == 1)
	    {
			//----------------------------------
			//	���һ�ֽ����ݷ���NACK�����STOP
			//----------------------------------
			I2C_AcknowledgeConfig(I2Cx, DISABLE); 
			I2C_GenerateSTOP(I2Cx, ENABLE);          
	    }
	
	    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); 
	    *pTmpBuf = I2C_ReceiveData(I2Cx);
	    pTmpBuf++; 
	    rev_len--;       
	}
	
	// -----------------------------------
	// ʹ��I2CӦ��
	// -----------------------------------	
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}

static void Delay(void)
{
	volatile uint32_t n = 0x00080000;
	uint32_t i = 0;
	for(i = 0; i < n; i ++)
	{
		;
	}
}

void I2C_Hard_Example(void)
{
	uint8_t apdu[] = {0x00,0x05,0x00,0x84,0x00,0x00,0x08,0x8C};
	uint16_t apdu_len = 8;
	uint8_t res[32];
	uint16_t resLen = 0;
	
	Delay();
	
	I2C_Init_Config();
	I2C_Write(apdu,apdu_len);
	I2C_Read(res,&resLen);
	
	while(1)
	{
		apdu_len = 0;
	}
}