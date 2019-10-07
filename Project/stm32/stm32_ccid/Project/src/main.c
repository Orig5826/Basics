/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   CCID demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "i2c_hard.h"
#include <string.h>

/* CCID 相关命令 */
void CCID_Command(void);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
__IO uint32_t TimingDelay = 0;
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/
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
	
	// 注意：STM32 上电第一个字节丢失问题
	// 在写第一个字节之前，需要先清除TC标志
	// 1.读取SR，然后写入DR(复位的时候，直接写入DR，没有读取SR过程，若没有手动清除TC，
	//		会出现上述情况)
	USART_GetFlagStatus(USART1, USART_FLAG_TC);	//1.
}

void UartSendString(const uint8_t *str, uint32_t strlen)
{
	uint32_t i = 0;
	
	if (0 == strlen)
	{
		for (i = 0; *str != '\0'; i++)
		{
			USART_SendData(USART1, *str);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
				; //等待数据发送完,需要放在USART_SendData前面，否则丢失上电的第一个字节
			str++;
		}
	}
	else
	{
		for (i = 0; i < strlen; i++)
		{
			USART_SendData(USART1, *str);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
				; //等待数据发送完,需要放在USART_SendData前面，否则丢失上电的第一个字节
			str++;
		}
	}
}

void UartSendHex(const uint8_t *str, uint32_t strlen)
{
	uint32_t i = 0;
	uint8_t temp = 0;
	uint8_t enter[3] = "\r\n";
	
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

	for (i = 0; i < 2; i++)
	{
		USART_SendData(USART1, enter[i]);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
			; //等待数据发送完
	}
}

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
  I2C_Init_Config();

  UartInit();
  UartSendString((uint8_t*)"Uart OK!\r\n",0);

  Set_System();
  USB_Interrupts_Config();
  Set_USBClock();
  
  Delay(200000);
  USB_Init();
  UartSendString((uint8_t*)"USB_Init\r\n",0);
  while (1)
  {
    CCID_Command();
  }
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(__IO uint32_t nCount)
{
  TimingDelay = nCount;
  for(; nCount!= 0;nCount--);
}

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while(1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
