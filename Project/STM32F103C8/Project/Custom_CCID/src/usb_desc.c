/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Descriptors for Custom HID Demo
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
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize40*/
    0x83,                       /*idVendor (0x0483)*/
    0x04,
    0x5C,                       /*idProduct = 0x545C "TL"(Tool)*/
    0x54,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing
                                              manufacturer */
    2,                          /*Index of string descriptor describing
                                             product*/
    3,                          /*Index of string descriptor describing the
                                             device serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* CustomHID_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    CUSTOMHID_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0x80,         /* bmAttributes: bit6=1 -> Self powered */
    0x32,         /* MaxPower 100 mA: this current is used for detecting Vbus */

    /************** Descriptor of Custom HID interface ****************/
    /* 09 */
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x02,         /* bNumEndpoints */
/* CCID */
    0x0B,         /* bInterfaceClass: HID */
    0x00,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x00,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */

/* Class Descriptor */
	0x36,					//bLength
	0x21,					//bDescriptorType	: CCID
	0x00, 0x01,				//bcdCCID			: v1.1
	0x00,					//bMaxSlotIndex		: [00,...,0F]
	0x01,					//bVoltageSupport	: 01->5V  02->3V  04->1.8V
	0x01, 0x00, 0x00, 0x00, //dwProtocols		: 01->T=0    02->T=1    03->T0&T1
	0xfc, 0x0d, 0x00, 0x00, //dwDefaultClock	: 3.58MHz
	0xfc, 0x0d, 0x00, 0x00, //dwMaximumClock	: 3.58MHz
	0x00,					//bNumClockSupported: should be non-zero according to ccid driver
	0x80, 0x25, 0x00, 0x00, //dwDataRate		: bps=9600 (00002580h <- 9600)
	0x80, 0x25, 0x00, 0x00, //dwMaxDataRate		: MAX bps=9600 (0001C200h <- 115200)
	0x00,					//bNumDataRatesSupported: should be non-zero according to ccid driver
	0x00, 0x00, 0x00, 0x00, //dwMaxIFSD
	0x00, 0x00, 0x00, 0x00, //dwSynchProtocols
	0x00, 0x00, 0x00, 0x00, //dwMechanical
	0x40, 0x08, 0x02, 0x00, //dwFeatures
	0x0f, 0x01, 0x00, 0x00, //dwMaxCCIDMessageLength: 271
	0xff,					//bClassGetResponse
	0xff,					//bClassEnvelope
	0x00, 0x00,				//wLcdLayout
	0x00,					//bPINSupport
	0x01,					//bMaxCCIDBusySlots

    /******************** Descriptor of Custom HID endpoints ******************/
    /* 27 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */

    0x81,          /* bEndpointAddress: Endpoint Address (IN) */
    0x03,          /* bmAttributes: Interrupt endpoint */
    0x40,          /* wMaxPacketSize: 64 Bytes max */
    0x00,
    0x20,          /* bInterval: Polling Interval (32 ms) */
    /* 34 */
    	
    0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: */
			/*	Endpoint descriptor type */
    0x01,	/* bEndpointAddress: */
			/*	Endpoint Address (OUT) */
    0x03,	/* bmAttributes: Interrupt endpoint */
    0x40,	/* wMaxPacketSize: 64 Bytes max  */
    0x00,
    0x20,	/* bInterval: Polling Interval (20 ms) */
    /* 41 */
  }
  ; /* CustomHID_ConfigDescriptor */


const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] = {
  0x06, 0x00, 0xFF, //Usage Page:
  0x09, 0x01,		  //Usage: Undefined
  0xa1, 0x01,		  //Collection
  0x15, 0x00,		  //Logical Minimum
  0x25, 0xFF,		  //Logical Maximum
  0x19, 0x01,		  //Usage Minimum
  0x29, 0x08,		  //Usage Maximum
  0x95, 0x40,		  //Report Count
  0x75, 0x08,		  //Report Size
  0x81, 0x02,		  //Input (Data, Variable, Absolute,Buffered Bytes)
  0x19, 0x01,		  //Usage Minimum
  0x29, 0x08,		  //Usage Maximum
  0x91, 0x02,		  //Feature (Data, Variable, Absolute,Buffered Bytes)
  0xc0			  //End Collection
};

/* USB String Descriptors (optional) */
const uint8_t CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID] =
  {
    CUSTOMHID_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
  {
    CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8_t CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =
  {
    CUSTOMHID_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'S', 0,
    'N', 0, 'P', 0, ' ', 0, 'T', 0, 'O', 0, 'O', 0, 'L', 0,
    ' ', 0
  };
uint8_t CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =
  {
    CUSTOMHID_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'v', 0, '1', 0, '.', 0,'0', 0,'0', 0
  };

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

