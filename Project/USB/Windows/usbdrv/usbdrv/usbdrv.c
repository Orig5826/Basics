#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <setupapi.h>
#include "usbdrv.h"



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
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	GUID guid = s_guid;	//GUID_DEVINTERFACE_MCHPUSB;

	wsprintf((PWCHAR)lpSubKey,
		TEXT("SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum"),NULL);
#if 0
	returnStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		lpSubKey,
		0L,
		KEY_READ,        //Changed from v1.0.  Used to be "KEY_ALL_ACCESS" which requires administrator logon (and application administrator execution level to work in Vista).
		&hKey);
	if (returnStatus == ERROR_SUCCESS)
	{
		printf("注册表打开成功\n");
		returnStatus = RegQueryValueEx(hKey,
			"Count",
			NULL,
			&dwType,
			(LPBYTE)&lszValue,
			&dwSize);
		if (returnStatus == ERROR_SUCCESS)
		{
			printf("注册表打开Count = %d\n", lszValue);
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
	wsprintf((PWCHAR)lpSubKey,
		TEXT("SYSTEM\\CURRENTCONTROLSET\\CONTROL\\DEVICECLASSES\\{%4.2x-%2.2x-%2.2x-%.2x%.2x-%.2x%.2x%.2x%.2x%.2x%.2x}\\%s"),
		guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7], pDevicePath);

	printf("%ls\n", lpSubKey);

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

		sprintf(pVid_Pid, "vid_%04x&pid_%04x", vid, pid);
		if (USBIO_IsVidPidEqual(intf_detail->DevicePath, pVid_Pid) == NULL)
		{
			SetupDiDestroyDeviceInfoList(info);
			free(intf_detail);
			return USBDRV_VIDPID_NOT_FOUND;
		}

		strcpy(dwDevicePath, intf_detail->DevicePath);
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
		}
		else
		{
			printf("--> 设备打开失败\n");
		}
	}

	SetupDiDestroyDeviceInfoList(info);
	return USBDRV_SUCCESS;
}
