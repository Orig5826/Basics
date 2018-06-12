/**
 * @brief 
 * 
 * @file i2c.h
 * @author wenjf
 * @date 2018-3-20
 */
#ifndef _I2C_H_
#define _I2C_H_

/*------------------------------------------------
 				1.	头文件
------------------------------------------------*/
#include "stm32f10x_conf.h"


extern u32 volatile g_TimeUs;
extern void SysTick_DelayUs(u32 TimeUs);
/*------------------------------------------------
				3.	函数声明
------------------------------------------------*/
void Init_I2c(void);
		//启动总线
void Start_I2c(void);
		//结束总线
void Stop_I2c(void);
		//字节数据传送函数
void SendByte(unsigned char c);
		//字节数据接收函数
unsigned char RcvByte(void);
		//应答子函数
void Ack_I2c(void);
		//非应答子函数
void NoAck_I2c(void);
		//向有子地址器件发送多字节数据函数 
unsigned char ISendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned int no);
		//向有子地址器件读取多字节数据函数
unsigned char IRcvStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned int no);
		//给从机发送数据
unsigned char I2C_Send(unsigned char slave_addr, unsigned char *sBuf, unsigned int sLen);
		//接收从机数据
unsigned char I2C_Recv(unsigned char slave_addr, unsigned char *rBuf, unsigned int rLen);
		// I2C Example
void I2C_Example(void);

/**********************************
			I2C总线
**********************************/
#endif
