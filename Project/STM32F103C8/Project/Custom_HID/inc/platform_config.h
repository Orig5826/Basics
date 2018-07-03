/**
  ******************************************************************************
  * @file    platform_config.h
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Evaluation board specific configuration file.
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "stm32f10x.h"

// 注意,这几个ID是随便弄的，后续修改
#define   UNIQUE_DEVICE_ID_BASE  (0x1FFFF7E8)
#define         ID1          (UNIQUE_DEVICE_ID_BASE) //(0x1FF80050)
#define         ID2          (UNIQUE_DEVICE_ID_BASE + 0x02) // (0x1FF80054)
#define         ID3          (UNIQUE_DEVICE_ID_BASE + 0x04) // (0x1FF80064)
#define ADC1_DR_Address                     ((uint32_t)0x4001244C)

// STM32F103C8T6
#define RCC_APB2Periph_GPIO_DISCONNECT RCC_APB2Periph_GPIOB
#define USB_DISCONNECT		GPIOB
#define USB_DISCONNECT_PIN	GPIO_Pin_8
#define RCC_APB2Periph_ALLGPIO                 (RCC_APB2Periph_GPIOA \
                                              | RCC_APB2Periph_GPIOB \
                                              | RCC_APB2Periph_GPIOC \
                                              | RCC_APB2Periph_GPIOD \
                                              | RCC_APB2Periph_GPIOE \
                                              | RCC_APB2Periph_GPIOF )
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

