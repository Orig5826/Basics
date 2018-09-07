#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <setupapi.h>
#include "usbdrv.h"

// 注意，该代码再非UNICODE下正常使用
// 我对编码相关的错误，暂时处理由困难
// 因此先不用UNICODE，先保证通讯正常
#undef UNICODE

#pragma comment(lib,"setupapi.lib")

// USB Mass Storage Device 
// GUID = {a5dcbf10-6530-11d2-901f-00c04fb951ed}
static const GUID s_guid = GUID_MASS_STORAGE_DEVICE;
static PCHAR pVid_Pid[18];

USBDRV_API int8_t * UsbDrv_GetVersion()
{
	return USBDRV_VERSION;
}

DWORD _stdcall USBIO_IsVidPidEqual(PCHAR pDevicePath, PCHAR pVidPid)
{
	DWORD dwResult = USBDRV_FAILED;
	char lszValue[255];
	char lpSubKey[512];

	HKEY hKey;
	LONG returnStatus;
	DWORD dwType = REG_DWORD;
	DWORD dwSize = 255;
	DWORD Count = 0;
	GUID guid = s_guid;	//GUID_DEVINTERFACE_MCHPUSB;

#if 1
	wsprintf(lpSubKey,
		TEXT("SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum"),NULL);
	returnStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		lpSubKey,
		0L,
		KEY_READ,        //Changed from v1.0.  Used to be "KEY_ALL_ACCESS" which requires administrator logon (and application administrator execution level to work in Vista).
		&hKey);
	if (returnStatus == ERROR_SUCCESS)
	{
		returnStatus = RegQueryValueEx(hKey,
			"Count",
			NULL,
			&dwType,
			(LPBYTE)&Count,
			&dwSize);
		if (returnStatus == ERROR_SUCCESS)
		{
			printf("设备个数Count = %d\n", Count);
		}

		dwType = REG_SZ;
		dwSize = 255;
		returnStatus = RegQueryValueEx(hKey,
			"0",
			NULL,
			&dwType,
			(LPBYTE)&lszValue,
			&dwSize);
		if (returnStatus == ERROR_SUCCESS)
		{
			printf("设备信息Value = %s\n", lszValue);
		}
		else
		{
			printf("设备信息Value = ???\n");
		}

		for (uint32_t i = 0; i < dwSize; i++)
		{
			lszValue[i] = tolower(lszValue[i]);
			if (lszValue[i] == '\\')
			{
				lszValue[i] = '#';
			}
		}

		printf("Size = %d\n", dwSize);
		printf("设备信息Value = %s\n", lszValue + 4);
		printf("pDevicePathValue = %s\n", pDevicePath + 8);
		if (0 == memcmp(pDevicePath + 8, lszValue + 4,15))
		{
			printf("对比成功!");
			dwResult = 1;
		}
		else
		{
			dwResult = 0;
		}
	}
	else
	{
		printf("注册表打开失败\n");
	}

	RegCloseKey(hKey);
#else
	/* Modify DevicePath to use registry format */
	pDevicePath[0] = '#';
	pDevicePath[1] = '#';
	pDevicePath[3] = '#';

	//\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\USBSTOR\Enum
	//
	/* Form SubKey */
	wsprintf(lpSubKey,
		TEXT("SYSTEM\\CURRENTCONTROLSET\\CONTROL\\DEVICECLASSES\\{%4.2x-%2.2x-%2.2x-%.2x%.2x-%.2x%.2x%.2x%.2x%.2x%.2x}\\%s"),
		guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7], pDevicePath);

	printf("%s\n", lpSubKey);

	/* Open Key */
	returnStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		lpSubKey,
		0L,
		KEY_QUERY_VALUE,        //Changed from v1.0.  Used to be "KEY_ALL_ACCESS" which requires administrator logon (and application administrator execution level to work in Vista).
		&hKey);
	if (returnStatus == ERROR_SUCCESS)
	{
		returnStatus = RegQueryValueEx(hKey,
			"DeviceInstance",
			NULL,
			&dwType,
			(LPBYTE)&lszValue,
			&dwSize);
		if (returnStatus == ERROR_SUCCESS)
		{
			/*
			* The string info stored in 'DeviceInstance' is the same
			* across all Windows platforms: 98SE, ME, 2K, and XP.
			* Upper-case in 98SE,ME.
			* Converts all to lower-case anyway.
			*/
			//strlwr(lszValue);
			if (strstr(lszValue, pVidPid) != NULL)
			{
				dwResult = USBDRV_SUCCESS;
			}
		}
	}
	RegCloseKey(hKey);

	/* Modify DevicePath to use the original format */
	pDevicePath[0] = '\\';
	pDevicePath[1] = '\\';
	pDevicePath[3] = '\\';
#endif
	return dwResult;
}

USBDRV_API uint32_t UsbDrv_OpenDevice(uint16_t pid,uint16_t vid)
{
	HDEVINFO info;
	SP_DEVICE_INTERFACE_DATA intf_data;
	PSP_DEVICE_INTERFACE_DETAIL_DATA intf_detail;
	DWORD ReqLen;		//<! Get size of symbolic link
	DWORD instance = 0;
	HANDLE hDevHandle = INVALID_HANDLE_VALUE;
	char dwDevicePath[MAX_PATH];	// 设备路径 * 重点

	for (instance = 0; instance < USBDRV_DEVCNT_MAX; instance++)
	{
		info = SetupDiGetClassDevs(&s_guid,
			NULL,
			NULL,
			DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
		if (info == INVALID_HANDLE_VALUE)
		{
			SetupDiDestroyDeviceInfoList(info);
			return USBDRV_NO_INFO;
		}

		// Get interface data for the requested instance
		intf_data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		if (!SetupDiEnumDeviceInterfaces(info,
			NULL,
			&s_guid,
			instance,
			&intf_data))
		{
			SetupDiDestroyDeviceInfoList(info);
			return USBDRV_INVALID_INST;
		}

		SetupDiGetDeviceInterfaceDetail(info, &intf_data, NULL, 0, &ReqLen, NULL);
		intf_detail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(ReqLen * sizeof(char));
		if (intf_detail == NULL)
		{
			SetupDiDestroyDeviceInfoList(info);
			free(intf_detail);
			return USBDRV_NO_INFO;
		}
		// Get symbolic link name
		intf_detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		if (!SetupDiGetDeviceInterfaceDetail(info,
			&intf_data,
			intf_detail,
			ReqLen,
			NULL,
			NULL))
		{
			SetupDiDestroyDeviceInfoList(info);
			free(intf_detail);
			return USBDRV_NO_INFO;
		}

		sprintf((char *)pVid_Pid,(const char *)"vid_%04x&pid_%04x", vid, pid);
		if (USBIO_IsVidPidEqual(intf_detail->DevicePath,(PCHAR)pVid_Pid) == 0)
		{
			SetupDiDestroyDeviceInfoList(info);
			free(intf_detail);
			continue;
		}

		strcpy(dwDevicePath, intf_detail->DevicePath);

		printf("DevPath = %s\n", dwDevicePath);

		hDevHandle = CreateFile(dwDevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL);

		if (hDevHandle != INVALID_HANDLE_VALUE)
		{
			printf("--> 设备打开成功\n");

			BOOL bResult;
			DWORD nBytesWritten;
			OVERLAPPED gOverlapped;
			uint8_t cbw[31] = { 0x55,0x53,0x42,0x43,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x01,\
				0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			bResult = WriteFile(hDevHandle, cbw, 31, &nBytesWritten, &gOverlapped);
			if (!bResult)
			{
				printf("写入CBW失败,ErrCode = 0x%08x\n", GetLastError());
			}
			uint8_t data[8] = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88 };
			bResult = WriteFile(hDevHandle, data, 8, &nBytesWritten, &gOverlapped);
			if (!bResult)
			{
				printf("写入DATA失败,ErrCode = 0x%08x\n", GetLastError());
			}
			bResult = ReadFile(hDevHandle, data, 13, &nBytesWritten, &gOverlapped);
			if (!bResult)
			{
				printf("读取CSW失败,ErrCode = 0x%08x\n", GetLastError());
			}

			break;
		}
		else
		{
			printf("--> 设备打开失败\n");
		}
	}

	SetupDiDestroyDeviceInfoList(info);
	CloseHandle(hDevHandle);

	return USBDRV_SUCCESS;
}
