/**
  ******************************************************************************
  * @file    usb_prop.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   All processing related to CCID Demo
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
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;
__IO uint8_t EXTI_Enable;
__IO uint8_t Request = 0;
uint8_t Report_Buf[64];   
/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
  {
    EP_NUM,
    1
  };

DEVICE_PROP Device_Property =
  {
    CCID_init,
    CCID_Reset,
    CCID_Status_In,
    CCID_Status_Out,
    CCID_Data_Setup,
    CCID_NoData_Setup,
    CCID_Get_Interface_Setting,
    CCID_GetDeviceDescriptor,
    CCID_GetConfigDescriptor,
    CCID_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };
USER_STANDARD_REQUESTS User_Standard_Requests =
  {
    CCID_GetConfiguration,
    CCID_SetConfiguration,
    CCID_GetInterface,
    CCID_SetInterface,
    CCID_GetStatus,
    CCID_ClearFeature,
    CCID_SetEndPointFeature,
    CCID_SetDeviceFeature,
    CCID_SetDeviceAddress
  };

ONE_DESCRIPTOR Device_Descriptor =
  {
    (uint8_t*)CCID_DeviceDescriptor,
    CCID_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (uint8_t*)CCID_ConfigDescriptor,
    CCID_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR CCID_Class_Descriptor =
  {
    (uint8_t*)CCID_ConfigDescriptor + CCID_OFF_CLASS_DESC,
    CCID_SIZ_CCID_DESC
  };

ONE_DESCRIPTOR String_Descriptor[4] =
  {
    {(uint8_t*)CCID_StringLangID, CCID_SIZ_STRING_LANGID},
    {(uint8_t*)CCID_StringVendor, CCID_SIZ_STRING_VENDOR},
    {(uint8_t*)CCID_StringProduct, CCID_SIZ_STRING_PRODUCT},
    {(uint8_t*)CCID_StringSerial, CCID_SIZ_STRING_SERIAL}
  };

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*CCID_SetReport_Feature function prototypes*/
uint8_t *CCID_SetReport_Feature(uint16_t Length);

/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : CCID_init.
* Description    : CCID init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CCID_init(void)
{
  /* Update the serial number string descriptor with the data from the unique 
  ID*/
  Get_SerialNum();
    
  pInformation->Current_Configuration = 0;
  /* Connect the device */
  PowerOn();

  /* Perform basic device initialization operations */
  USB_SIL_Init();

  bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : CCID_Reset.
* Description    : CCID reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CCID_Reset(void)
{
  /* Set CCID_DEVICE as not configured */
  pInformation->Current_Configuration = 0;
  pInformation->Current_Interface = 0;/*the default Interface*/
  
  /* Current Feature initialization */
  pInformation->Current_Feature = CCID_ConfigDescriptor[7];
 
  SetBTABLE(BTABLE_ADDRESS);

  /* Initialize Endpoint 0 */
  SetEPType(ENDP0, EP_CONTROL);							// 端点0为控制端点
  SetEPTxStatus(ENDP0, EP_TX_STALL);					// 端点状态为发送无效，也就是主机IN令牌包来的时候，回送一个STALL。
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);						// --- 设置端点0描述符表，包括接收缓冲区地址、最大允许接收的字节数、发送缓冲区地址三个量。
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);						// --- 接收和发送缓冲区地址
  Clear_Status_Out(ENDP0);								// 清除EP_KIND的STATUS_OUT位，如果改位被设置，在控制模式下只对0字节数据包相应。其它的都返回STALL。主要用于控制传输的状态过程。
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);	// 接收缓冲区支持64个字节。
  SetEPRxValid(ENDP0);									// 使能端点0的接收，因为很快就要接收SETUP令牌包后面跟着的数据包了。

  /**
	2019.10.06 更新端点1&2初始化配置
	*/
  /* Initialize Endpoint 1 */
  SetEPType(ENDP1, EP_BULK);
  SetEPTxAddr(ENDP1, ENDP1_TXADDR);
  SetEPTxStatus(ENDP1, EP_TX_NAK);
  SetEPRxStatus(ENDP1, EP_RX_DIS);

  /* Initialize Endpoint 2 */
  SetEPType(ENDP2, EP_BULK);
  SetEPRxAddr(ENDP2, ENDP2_RXADDR);
  SetEPRxCount(ENDP2, Device_Property.MaxPacketSize);
  SetEPRxStatus(ENDP2, EP_RX_VALID);
  SetEPTxStatus(ENDP2, EP_TX_DIS);

  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPRxValid(ENDP0);

  /* Set this device to response on default address */
  SetDeviceAddress(0);
  bDeviceState = ATTACHED;
}
/*******************************************************************************
* Function Name  : CCID_SetConfiguration.
* Description    : Update the device state to configured and command the ADC 
*                  conversion.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CCID_SetConfiguration(void)
{
  if (pInformation->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
    
    /* Start ADC Software Conversion */ 
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)|| defined(STM32F37X)
    ADC_SoftwareStartConv(ADC1);
#elif defined(STM32F303xC) || defined(STM32F303xE)
    ADC_StartConversion(ADC1);
#else
    // ADC_SoftwareStartConvCmd(ADC1, ENABLE);
#endif /* STM32L1XX_XD */
  }
}
/*******************************************************************************
* Function Name  : CCID_SetConfiguration.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CCID_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}
/*******************************************************************************
* Function Name  : CCID_Status_In.
* Description    : Joystick status IN routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CCID_Status_In(void)
{  
  BitAction Led_State;
  
  if (Report_Buf[1] == 0)
  {
    Led_State = Bit_RESET;
  }
  else 
  {
    Led_State = Bit_SET;
  }
  
  switch (Report_Buf[0])  
  {
    /*Change LED's status according to the host report*/
    
  case 1: /* Led 1 */ 
    if (Led_State != Bit_RESET)
    {
//       STM_EVAL_LEDOn(LED1);
    }
    else
    {
//      STM_EVAL_LEDOff(LED1);
    }
    break;
  case 2:   /* Led 2 */    
    if (Led_State != Bit_RESET)
    {
//      STM_EVAL_LEDOn(LED2);
    }
    else
    {
//      STM_EVAL_LEDOff(LED2);
    }
    break;
  case 3:/* Led 3 */    
    if (Led_State != Bit_RESET)
    {
//      STM_EVAL_LEDOn(LED3);
    }
    else
    {
//      STM_EVAL_LEDOff(LED3);
    }
    break;
  case 4:/* Led 4 */    
    if (Led_State != Bit_RESET)
    {
//      STM_EVAL_LEDOn(LED4);
    }
    else
    {
//      STM_EVAL_LEDOff(LED4);
    }
    break;
  default:
//    STM_EVAL_LEDOff(LED1);
//    STM_EVAL_LEDOff(LED2);
//    STM_EVAL_LEDOff(LED3);
//    STM_EVAL_LEDOff(LED4); 
    break;
  }
}

/*******************************************************************************
* Function Name  : CCID_Status_Out
* Description    : Joystick status OUT routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CCID_Status_Out (void)
{
}

/*******************************************************************************
* Function Name  : CCID_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT CCID_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  
  if (pInformation->USBwIndex != 0) 
    return USB_UNSUPPORT;    
  
  CopyRoutine = NULL;
  
  if ((RequestNo == GET_DESCRIPTOR)
      && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
        )
  {
    if (pInformation->USBwValue1 == CCID_DESCRIPTOR_TYPE)
    {
      CopyRoutine = CCID_GetCCIDDescriptor;
    }
    
  } /* End of GET_DESCRIPTOR */
  
  /*** GET_PROTOCOL, GET_REPORT, SET_REPORT ***/
  else if ( (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) )
  {         
    switch( RequestNo )
    {
    case GET_PROTOCOL:
      CopyRoutine = CCID_GetProtocolValue;
      break;
    case SET_REPORT:
      CopyRoutine = CCID_SetReport_Feature;
      Request = SET_REPORT;
      break;
    default:
      break;
    }
  }
  
  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }
  
  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CCID_SetReport_Feature
* Description    : Set Feature request handling
* Input          : Length.
* Output         : None.
* Return         : Buffer
*******************************************************************************/
uint8_t *CCID_SetReport_Feature(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 2;
    return NULL;
  }
  else
  {
    return Report_Buf;
  }
}

/*******************************************************************************
* Function Name  : CCID_NoData_Setup
* Description    : handle the no data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT CCID_NoData_Setup(uint8_t RequestNo)
{
  if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == SET_PROTOCOL))
  {
    return CCID_SetProtocol();
  }

  else
  {
    return USB_UNSUPPORT;
  }
}

/*******************************************************************************
* Function Name  : CCID_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *CCID_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
* Function Name  : CCID_GetConfigDescriptor.
* Description    : Gets the configuration descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *CCID_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
* Function Name  : CCID_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *CCID_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  if (wValue0 >= 4)
  {
    return NULL;
  }
  else 
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
}


/*******************************************************************************
* Function Name  : CCID_GetCCIDDescriptor.
* Description    : Gets the CCID descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *CCID_GetCCIDDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &CCID_Class_Descriptor);
}

/*******************************************************************************
* Function Name  : CCID_Get_Interface_Setting.
* Description    : tests the interface and the alternate setting according to the
*                  supported one.
* Input          : - Interface : interface number.
*                  - AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : USB_SUCCESS or USB_UNSUPPORT.
*******************************************************************************/
RESULT CCID_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 0)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CCID_SetProtocol
* Description    : Joystick Set Protocol request routine.
* Input          : None.
* Output         : None.
* Return         : USB SUCCESS.
*******************************************************************************/
RESULT CCID_SetProtocol(void)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  ProtocolValue = wValue0;
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CCID_GetProtocolValue
* Description    : get the protocol value
* Input          : Length.
* Output         : None.
* Return         : address of the protocol value.
*******************************************************************************/
uint8_t *CCID_GetProtocolValue(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1;
    return NULL;
  }
  else
  {
    return (uint8_t *)(&ProtocolValue);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
