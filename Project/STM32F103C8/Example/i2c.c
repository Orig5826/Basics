/**
 * @brief IO模拟I2C总线
 * 
 * 从51迁移至stm32，用IO口软模拟
 * @file i2c.c
 * @author wenjf
 * @date 2018-3-20
 */
#include "i2c.h"
#include "timer.h"
#include "uart.h"

// 需要在主函数中调用...函数
#define _Nop(x) (SysTick_DelayUs(x))

//模拟I2C时钟控制位
#define I2C_SCL(x) (x == 1 ? GPIO_SetBits(GPIOB, 1 << 6) : GPIO_ResetBits(GPIOB, 1 << 6))

//模拟I2C数据传送位
#define I2C_SDA(x) (x == 1 ? GPIO_SetBits(GPIOB, 1 << 7) : GPIO_ResetBits(GPIOB, 1 << 7))

//获取SDA值，用于判断
#define I2C_GET_SDA() (GPIO_ReadInputDataBit(GPIOB, 1 << 7))

#define I2C_SDA_IN                                     \
	{                                                  \
		GPIO_InitTypeDef gpio_config;                  \
		GPIO_StructInit(&gpio_config);                 \
		gpio_config.GPIO_Speed = GPIO_Speed_10MHz;     \
		gpio_config.GPIO_Pin = GPIO_Pin_7;             \
		gpio_config.GPIO_Mode = GPIO_Mode_IN_FLOATING; \
		GPIO_Init(GPIOB, &gpio_config);                \
	}

#define I2C_SDA_OUT                                \
	{                                              \
		GPIO_InitTypeDef gpio_config;              \
		GPIO_StructInit(&gpio_config);             \
		gpio_config.GPIO_Speed = GPIO_Speed_10MHz; \
		gpio_config.GPIO_Pin = GPIO_Pin_7;         \
		gpio_config.GPIO_Mode = GPIO_Mode_Out_PP;  \
		GPIO_Init(GPIOB, &gpio_config);            \
	}

/**
 * @brief 全局变量，用来判定SystemTick延时
 * 
 * 之前出现了一个很奇怪的现象。
 * 串口发送函数调用单数次卡死，双数次正常
 * (调试发现不是卡死，而是g_TimeUs便的太大，而导致一直在while循环中出不来。但这和逻辑不符合呀)
 * 终于想到了可能是优化导致的在中断中被改变，但优化之后，并没有直接读取该值，二十为了快速读取了寄存器中的值。
 * 而导致出现的g_TimeUs在某种特定情况下发生逻辑错误。于是添加了volatile关键字修饰。问题解决。
 */
u32 volatile g_TimeUs = 0;
/**
 * @brief 
 * 
 * 需要在调用该函数前配置：SysTick_Config <- core_cm3.h
 * 若为72MHz，则配置为72即可得到1us的延时
 * 可选配置：
 * SysTick_CLKSourceConfig <- misc.h
 * 这个似乎是可以配置时钟源的，暂时没有详细	研究。
 * @param TimeUs 延时时间，以Us为单位
 */
void SysTick_DelayUs(u32 TimeUs)
{
	g_TimeUs = TimeUs;
	while (g_TimeUs--)
		;
}
/**
 * @brief I2C 例程
 * 
 */
#define SLAVE_ADDR		0x55
void I2C_Example(void)
{
#define BUF_SIZE	8
	uint8_t sBuf[BUF_SIZE] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
	uint8_t rBuf[BUF_SIZE] = {0};
	
	SysTick_Config(72);
	
	LED_Init();
	UartInit();
	Init_I2c();
	UartSendString((const u8 *)"I2C OK!\r\n",9);
	//UartSendString((const u8 *)"I2C OK!\r\n",0);
	while (1)
	{
		I2C_Send(SLAVE_ADDR,sBuf,BUF_SIZE);
		I2C_Recv(SLAVE_ADDR,rBuf,BUF_SIZE);
		UART_SendHex(sBuf,BUF_SIZE);
		UART_SendHex(rBuf,BUF_SIZE);
		
		SysTick_DelayUs(500000);
	}
}

/**
  * @brief  初始化I2C模块
  * @param  None
  * @retval None
  */
void Init_I2c(void)
{
	GPIO_InitTypeDef gpio_config;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_StructInit(&gpio_config);
	gpio_config.GPIO_Speed = GPIO_Speed_10MHz;

	//将PB6和PB7配置为I2C复用引脚
	gpio_config.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio_config.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpio_config);
}

/**
  * @brief  I2C总线启动
  * @param  None
  * @retval None
  */
void Start_I2c(void)
{
	I2C_SDA_OUT
	I2C_SDA(1); //发送起始条件的数据信号

	_Nop(1);
	I2C_SCL(1);

	//起始条件建立时间大于4.7us，延时
	_Nop(5);

	I2C_SDA(0); //发起起始信号

	//起始条件锁定时间大于4us
	_Nop(5);

	I2C_SCL(0); //钳住I2C总线，准备发送或接收数据
	_Nop(2);
}

/**
  * @brief  I2C总线结束
  * @param  None
  * @retval None
  */
void Stop_I2c(void)
{
	I2C_SDA_OUT
	I2C_SDA(0); //发送结束条件的数据信号

	//结束条件建立时间大于4u
	_Nop(1);

	I2C_SCL(1);

	//结束条件建立时间大于4u
	_Nop(5);

	I2C_SDA(1); //发送I2C总线结束信号
	_Nop(10);	//间隔太短，感觉不稳定，因此修改为10
}

/**
  * @brief  I2C总线，字节发送，发送完毕之后，等待应答
  * @param  unsigned char -> 发送的数据
  * @retval None
  * 
  * 全局变量 ack=1,正确应答
  *          ack=0，非应答
  */
void SendByte(unsigned char c)
{
	unsigned char BitCnt; //位数

	I2C_SCL(0);

	//先配置为输出
	I2C_SDA_OUT

	for (BitCnt = 0; BitCnt < 8; BitCnt++) //要发送的数据长度为8位
	{
		if ((c << BitCnt) & 0x80) //判断发送位
		{
			I2C_SDA(1);
		}
		else
		{
			I2C_SDA(0);
		}

		I2C_SCL(1); //置时钟线为高，通知被遥控开始接收数据位

		//保证时钟高电平周期大于4us
		_Nop(5);
		I2C_SCL(0);
	}
}

/**
  * @brief  等待应答
  * @param  None
  * @retval unsigned char 接收到的数据
  */
unsigned char WaitAck()
{
	unsigned char ack = 0;
	_Nop(2);
	I2C_SDA(1);
	_Nop(2);

	//-------------------------------
	//	配置SDA为输入，等待接受ACK
	//-------------------------------
	I2C_SDA_IN
	I2C_SCL(1);

	_Nop(3);

	if (1 == I2C_GET_SDA()) //判断是否接收到应答信号
	{
		ack = 0;
	}
	else
	{
		ack = 1; //应答
	}

	I2C_SCL(0);
	_Nop(2);

	return ack;
}

/**
  * @brief  I2C总线，Byte接收
  * @param  None
  * @retval unsigned char 接收到的数据
  */
unsigned char RcvByte(void)
{
	unsigned char retc;
	unsigned char BitCnt;

	retc = 0;
	I2C_SDA_IN

	for (BitCnt = 0; BitCnt < 8; BitCnt++)
	{
		_Nop(1);
		I2C_SCL(0); //置时钟线为低，准备接收数据位

		//时钟低电平周期大于4.7us
		_Nop(5);
		I2C_SCL(1);
		_Nop(2);
		retc = retc << 1;

		if (1 == I2C_GET_SDA()) //读数据位，接收的数据放入retc中
		{
			retc = retc + 1;
		}

		_Nop(2);
	}

	I2C_SCL(0);
	_Nop(2);

	return (retc);
}

/** @brief  I2C总线应答
  * @param  None
  * @retval None
  */
void Ack_I2c(void)
{
	//配置为输出
	I2C_SDA_OUT
	I2C_SDA(0); //注意：应答是拉低

	_Nop(5);

	I2C_SCL(1);

	//时钟低电平周期大于4us
	_Nop(5);

	//清时钟线，钳住I2C总线以便于继续接收
	I2C_SCL(0);
	_Nop(2);
}

/** @brief  I2C总线非应答
  * @param  None
  * @retval None
  */
void NoAck_I2c(void)
{
	//配置为输出
	I2C_SDA_OUT
	I2C_SDA(1);

	_Nop(3);
	I2C_SCL(1);

	//时钟低电平周期大于4us
	_Nop(5);

	I2C_SCL(0); //清时钟线，钳住I2C总线以便于继续接收
	_Nop(2);
}

/** @brief  I2C总线非应答
  * @param  sla Slave设备地址，这个地址需要算上R/W bit
  * @param  suba Slave设备寄存器地址
  * @param  s 要发送的数据
  * @param  s 要发送的数据个数
  * @retval 1.正确应答 0.发生非应答
  */
unsigned char ISendStr(unsigned char sla, unsigned char suba, unsigned char *s, unsigned int no)
{
	unsigned char i;

	Start_I2c();   //启动总线
	SendByte(sla); //发送器件地址

	if (0 == WaitAck())
		return (0);

	SendByte(suba); //发送器件子地址

	if (0 == WaitAck())
		return (0);

	for (i = 0; i < no; i++)
	{
		SendByte(*s); //发送数据

		if (0 == WaitAck())
			return (0);

		s++;
	}

	Stop_I2c(); //结束总线
	return (1);
}

/** @brief  I2C总线非应答
  * @param  sla Slave设备地址，这个地址需要算上R/W bit
  * @param  suba Slave设备寄存器地址
  * @param  s 接收数据的存放地址
  * @param  s 要接收的数据个数
  * @retval 1.正确应答 0.发生非应答
  */
unsigned char IRcvStr(unsigned char sla, unsigned char suba, unsigned char *s, unsigned int no)
{
	unsigned char i;

	Start_I2c();   //启动总线
	SendByte(sla); //发送器件地址

	if (0 == WaitAck())
	{
		return (0);
	}

	SendByte(suba); //发送器件子地址

	if (0 == WaitAck())
		return (0);

	Start_I2c();
	SendByte(sla + 1); //此处表示读取

	if (0 == WaitAck())
		return (0);

	for (i = 0; i < no - 1; i++)
	{
		*s = RcvByte(); //发送数据
		Ack_I2c();		//发送就答位
		s++;
	}

	*s = RcvByte();
	NoAck_I2c(); //发送非应位
	Stop_I2c();  //结束总线
	return (1);
}

/**
 * @brief  I2C发送数据
 * 
 * @param slave_addr 从设备地址(实际地址，不包括读写bit位)，共7bit
 * @param sBuf 发送的数据
 * @param sLen 发送的数据长度
 * @return unsigned char 
 * 		@arg 1.1.正确应答
 * 		@arg 0.发生非应答
 */
unsigned char I2C_Send(unsigned char slave_addr, unsigned char *sBuf, unsigned int sLen)
{
	unsigned char i;

	Start_I2c();				 //启动总线
	SendByte((slave_addr << 1)); //发送器件地址

	if (0 == WaitAck())
		return (0);

	for (i = 0; i < sLen; i++)
	{
		SendByte(*sBuf); //发送数据

		if (0 == WaitAck())
			return (0);

		sBuf++;
	}

	Stop_I2c(); //结束总线
	return (1);
}

/**
 * @brief I2C接收数据
 * 
 * @param slave_addr 从设备地址(实际地址，不包括读写bit位)，共7bit
 * @param rBuf 接收数据的缓存
 * @param rLen 接收的数据个数
 * @return unsigned char 
 * 		@arg 1.1.正确应答
 * 		@arg 0.发生非应答
 */
unsigned char I2C_Recv(unsigned char slave_addr, unsigned char *rBuf, unsigned int rLen)
{
	unsigned char i;

	Start_I2c();		  //启动总线
	SendByte((slave_addr << 1) | 0x01); //发送器件地址

	if (0 == WaitAck())
	{
		return (0);
	}
	
	for (i = 0; i < rLen - 1; i++)
	{
		*rBuf = RcvByte(); //发送数据
		Ack_I2c();		   //发送就答位
		rBuf++;
	}

	*rBuf = RcvByte();
	NoAck_I2c(); //发送非应位
	Stop_I2c();  //结束总线
	return (1);
}
