#pragma once

#include "typedef.h"

// API 接口类型
#define USBDRV_API	

// usbdrv 相关信息
#define USBDRV_VERSION				"1.0.00"	//<! version = 1.0.00
#define USBDRV_DEVCNT_MAX           127

//
#define USBDRV_VID					0x090C
#define USBDRV_PID					0x1000
#define USBDRV_VID_PID				"vid_03eb&pid_0205";
#define GUID_MASS_STORAGE_DEVICE	{ 0xa5dcbf10, 0x6530, 0x11d2, { 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed } }


// Error Information
#define USBDRV_SUCCESS				0
#define USBDRV_FAILED				1
#define	USBDRV_NO_INFO				2
#define	USBDRV_INVALID_INST			3
#define	USBDRV_VIDPID_NOT_FOUND		4
#define USBDRV_NOT_ATTACHED			5


/*
 * USBDRV_API
 */
USBDRV_API int8_t * UsbDrv_GetVersion();
USBDRV_API uint32_t UsbDrv_OpenDevice(uint16_t pid, uint16_t vid);
