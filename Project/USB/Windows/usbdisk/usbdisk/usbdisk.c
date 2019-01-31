
#define DLL_EXPORTS
#include "usbdisk.h"

#include <windows.h>
#include <SetupAPI.h>
#include <Cfgmgr32.h>

#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>

#include <devioctl.h>
#include <ntddstor.h>
#include <ntddscsi.h>

#pragma comment(lib, "setupapi.lib")

GUID GUID_GLOBAL = { 0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b };
//udisk
//GUID GUID_GLOBAL = {0x53f56308L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b};
//cdrom

/*
 * 文件作用域变量
 */
static HANDLE s_Handle;
static uint8_t usbdisk_debug_level = 1;
/*
 *	函数声明
 */
static BOOL usb_scsi_cmd(HANDLE hDevHandle, UCHAR Direction, PUCHAR pData, DWORD Data_Length, PUCHAR CB, UCHAR CBLength, PUCHAR resData, PDWORD resLen);
static void  FormatErrorCode(void)
{
	static char szBuf[128];
	LPVOID lpMsgBuf;
	DWORD ErrorCode = GetLastError();
	memset(szBuf, 0x00, 128);
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		ErrorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	sprintf(szBuf,
		"[错误代码 = %d]: %s",
		ErrorCode, (char *)lpMsgBuf);
	printf("%s\n", szBuf);

	LocalFree(lpMsgBuf);
}


int GetDevicePath(int num, LPTSTR path)
{
	HDEVINFO hardwareDeviceInfo;
	SP_INTERFACE_DEVICE_DATA deviceInfoData;
	int result;
	ULONG requiredLength;
	ULONG predictedLength;
	PSP_INTERFACE_DEVICE_DETAIL_DATA functionClassDeviceData;

	hardwareDeviceInfo = SetupDiGetClassDevs(
		&GUID_GLOBAL,
		NULL, // Define no enumerator (global)
		NULL, // Define no
		(DIGCF_PRESENT | // Only Devices present
		DIGCF_INTERFACEDEVICE)); // Function class devices.

	deviceInfoData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

	result = SetupDiEnumDeviceInterfaces(hardwareDeviceInfo,
		0, // We don't care about specific PDOs
		&GUID_GLOBAL,
		num,
		&deviceInfoData);

	if (result)
	{
		SetupDiGetInterfaceDeviceDetail(
			hardwareDeviceInfo,
			&deviceInfoData,
			NULL,                   // probing so no output buffer yet
			0,                      // probing so output buffer length of zero
			&requiredLength,
			NULL);                  // not interested in the specific dev-node


		predictedLength = requiredLength;

		functionClassDeviceData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(predictedLength);

		functionClassDeviceData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

		result = SetupDiGetInterfaceDeviceDetail(
			hardwareDeviceInfo,
			&deviceInfoData,
			functionClassDeviceData,
			predictedLength,
			&requiredLength,
			NULL);

		if (result)
		{
			strcpy(path, functionClassDeviceData->DevicePath);
		}

		free(functionClassDeviceData);
	}

	SetupDiDestroyDeviceInfoList(hardwareDeviceInfo);

	return result;
}


/*
* SymLink 长度必须为36-4-4 = 28字节
* 其中VID占8字节，PID占16字节，Version（n.nn）占4字节
*/
static HANDLE usb_find(char * SymLink,int Len)
{
	HANDLE hDevHandle = NULL;
	char DevPath[256];

	// 必须保证长度正确
	if (Len > 28)
	{
		printf("The Length of SymLink Is Overflow!\n");
		return NULL;
	}

	// 通过Inquiry命令过滤设备
#if 0
	// 通过磁盘盘符，打开设备。
	for (char c = 'C'; c < 'Z'; c++)
	{
		sprintf(DevPath, "\\\\.\\%c:", c);
#else
	int rv = 0;
	for (int i = 0; i < 256; i++)
	{
		rv = GetDevicePath(i, DevPath);
		if (!rv)
		{
			return 0;
		}
#endif
		// 通过CreateFile打开相应的设备
		hDevHandle = CreateFile(DevPath,
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		if (hDevHandle == INVALID_HANDLE_VALUE)
		{
			printf("设备[%s]打开失败\n",DevPath);
			FormatErrorCode();

			printf("可能原因：\n"
				"	1.需要管理员权限\n"
				"	2.设备名称是否正确\n");
			goto Exit;
		}

		UCHAR InquiryData[37] = {0};
		DWORD InquiryDataLen = 32;
		UCHAR CB[0x10] = { 0x12,0x00,0x00,0x00,0x24 };
		usb_scsi_cmd(hDevHandle, SCSI_IOCTL_DATA_IN, NULL, 36, CB, 0x06, InquiryData, &InquiryDataLen);
		if (InquiryDataLen != 36)
		{
			printf("InquiryDataLen -> Error!\n");
		}

		// 暂不对前8字节进行过滤，因有时存在盘符，有时又不需要盘符。
		//if (0 == memcmp(InquiryData, "\x00\x80\x02\x02\x1f\x00\x00\x00", 8))
		{
			if (0 == memcmp(InquiryData + 8, SymLink, Len))
			{
				printf("找到设备: [%s]\n", InquiryData + 8);
				return hDevHandle;
			}
		}
		CloseHandle(hDevHandle);
	}

Exit:
	CloseHandle(hDevHandle);
	printf("----- END -----\n");
	system("pause");
	return NULL;
}

#define SPT_SENSE_LENGTH 32
#define SPTWB_DATA_LENGTH 2048
typedef struct _SCSI_PASS_THROUGH_WITH_BUFFERS {
	SCSI_PASS_THROUGH spt;
	ULONG             Filler;      // realign buffers to double word boundary
	UCHAR             ucSenseBuf[SPT_SENSE_LENGTH];
	UCHAR             ucDataBuf[SPTWB_DATA_LENGTH];
} SCSI_PASS_THROUGH_WITH_BUFFERS, *PSCSI_PASS_THROUGH_WITH_BUFFERS;
static BOOL usb_scsi_cmd(HANDLE hDevHandle, UCHAR Direction, PUCHAR pData, DWORD Data_Length, PUCHAR CB, UCHAR CBLength, PUCHAR resData, PDWORD resLen)
{
	BOOL status = FALSE;
	SCSI_PASS_THROUGH_WITH_BUFFERS sptwb;
	ULONG length = 0, returned = 0;

	ZeroMemory(&sptwb, sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));
	sptwb.spt.Length = sizeof(SCSI_PASS_THROUGH);
	sptwb.spt.PathId = 0;
	sptwb.spt.TargetId = 1;
	sptwb.spt.Lun = 0;
	sptwb.spt.SenseInfoLength = SPT_SENSE_LENGTH;
	sptwb.spt.SenseInfoOffset =
		offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS, ucSenseBuf);

	// Directiong & TimeOut
	sptwb.spt.TimeOutValue = 2;
	sptwb.spt.DataIn = Direction;
	// Data
	sptwb.spt.DataTransferLength = Data_Length;
	if (pData != NULL && sptwb.spt.DataIn == SCSI_IOCTL_DATA_OUT)
	{
		for (DWORD i = 0; i < Data_Length; i++)
		{
			sptwb.ucDataBuf[i] = pData[i];
		}
	}
	sptwb.spt.DataBufferOffset =
		offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS, ucDataBuf);

	// CB
	sptwb.spt.CdbLength = CBLength;
	for (UCHAR i = 0; i < CBLength; i++)
	{
		sptwb.spt.Cdb[i] = CB[i];
	}
	//
	length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS, ucDataBuf) +
		sptwb.spt.DataTransferLength;

	status = DeviceIoControl(hDevHandle,
		IOCTL_SCSI_PASS_THROUGH,
		&sptwb,
		sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS),
		&sptwb,
		length,
		&returned,
		FALSE);
	if (status != TRUE)
	{
		printf("DeviceIoControl 出错！\n");
		FormatErrorCode();
		status = FALSE;
	}
	else
	{
		if (usbdisk_debug_level >= 3)
		{
			printf("[CMD]:0x%02x\n", CB[0]);
		}
		switch (Direction)
		{
		case SCSI_IOCTL_DATA_IN:
			if (usbdisk_debug_level >= 3)
			{
				printf("\t\t[IN]:\n");
				usb_display(sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
			}
			memcpy(resData, sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
			*resLen = sptwb.spt.DataTransferLength;
			break;
		case SCSI_IOCTL_DATA_OUT:
			if (usbdisk_debug_level >= 3)
			{
				printf("\t\t[OUT]:\n");
				usb_display(sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
			}
			*resLen = 0;
		case SCSI_IOCTL_DATA_UNSPECIFIED:
			//printf("\n");
			break;
		default:
			break;
		}
		status = TRUE;
	}
	return status;
}


// ---------------------------------------------------------
DLL_API void CALL usb_display(PUCHAR buffer, DWORD size)
{
	DWORD i, j, k;
	printf("\t");
	for (i = 0; i < size; i += 16)
	{
		for (j = 0, k = 0; k < 16; j++, k++)
		{
			if (i + j < size)
			{
				printf("%02x", buffer[i + j]);
			}
			else
			{
				printf("  ");
			}
			printf(" ");
		}
		// 显示相应的assic码
		if (usbdisk_debug_level >= 2)
		{
			printf("    ");
			for (j = 0, k = 0; k < 16; j++, k++)
			{
				if (i + j < size)
				{
					if ((buffer[i + j] < 32) || (buffer[i + j] > 126))
					{
						printf(".");
					}
					else
					{
						printf("%c", buffer[i + j]);
					}
				}
			}
		}
		if (i + 16 < size)
		{
			printf("\n\t");
		}
		else
		{
			printf("\n");
		}
	}
}

DLL_API bool CALL usb_open(PUCHAR symbolic_link)
{
	int Len;
	Len = strlen(symbolic_link);
	s_Handle = usb_find(symbolic_link,Len);
	if (s_Handle == NULL)
	{
		return FALSE;
	}
	else
	{
		printf("---------------- 打开USB设备 ----------------\n");
	}
	return TRUE;
}

DLL_API void CALL usb_close(void)
{
	if (FALSE == CloseHandle(s_Handle))
	{
		printf("设备关闭失败\n");
		FormatErrorCode();
	}
	else
	{
		printf("---------------- 关闭USB设备 ----------------\n");
	}
}

DLL_API void CALL usb_set_debug_level(uint8_t debug_level)
{
	usbdisk_debug_level = debug_level;
}

DLL_API bool CALL usb_write(uint8_t * sBuf, uint32_t sLen)
{
	DWORD rLen = 0;		//此处无用，仅仅是为了函数参数的调用
	UCHAR CB[31] = {0xff};
	if (usbdisk_debug_level >= 1 && usbdisk_debug_level <= 2)
	{
		printf("[Write]:\n");
		usb_display(sBuf, sLen);
	}
	return usb_scsi_cmd(s_Handle, SCSI_IOCTL_DATA_OUT, sBuf, sLen, CB, 1, NULL, &rLen);
}
DLL_API bool CALL usb_read(uint8_t * rBuf, uint32_t * rLen)
{
	BOOL ret = FALSE;
	UCHAR CB[31] = { 0xff };

	ret = usb_scsi_cmd(s_Handle, SCSI_IOCTL_DATA_IN, NULL, *rLen, CB, 1, rBuf, (PDWORD)rLen);
	if (ret != FALSE)
	{
		if (usbdisk_debug_level >= 1 && usbdisk_debug_level <= 2)
		{
			printf("[Read]:\n");
			usb_display(rBuf,*rLen);
		}
	}
	return ret;
}

DLL_API bool CALL usb_write_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * sBuf, uint32_t sLen)
{
	DWORD rLen = 0;		//此处无用，仅仅是为了函数参数的调用
	UCHAR CB[31] = { 0xfd };
	if (apdu_len > 15)
	{
		return FALSE;
	}
	memcpy(CB + 1, apdu, apdu_len);

	if (usbdisk_debug_level >= 1 && usbdisk_debug_level <= 2)
	{
		printf("[Write_HS]:\n");
		usb_display(sBuf, sLen);
	}
	return usb_scsi_cmd(s_Handle, SCSI_IOCTL_DATA_OUT, sBuf, sLen, CB, apdu_len + 1, NULL, &rLen);
}
DLL_API bool CALL usb_read_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * rBuf, uint32_t * rLen)
{
	BOOL ret = FALSE;
	UCHAR CB[31] = { 0xfe };
	if (apdu_len > 15)
	{
		return FALSE;
	}
	memcpy(CB + 1, apdu, apdu_len);

	ret = usb_scsi_cmd(s_Handle, SCSI_IOCTL_DATA_IN, NULL, *rLen, CB, apdu_len + 1, rBuf, (PDWORD)rLen);
	if (ret != FALSE)
	{
		if (usbdisk_debug_level >= 1 && usbdisk_debug_level <= 2)
		{
			printf("[Read_HS]:\n");
			usb_display(rBuf, *rLen);
		}
	}
	return ret;
}

#if 0
BOOL APIENTRY DllMain(
	HANDLE hModule,             // DLL模块的句柄
	DWORD ul_reason_for_call,   // 调用本函数的原因
	LPVOID lpReserved           // 保留
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//进程正在加载本DLL
		break;
	case DLL_THREAD_ATTACH:
		//一个线程被创建
		break;
	case DLL_THREAD_DETACH:
		//一个线程正常退出
		break;
	case DLL_PROCESS_DETACH:
		//进程正在卸载本DLL
		break;
	}
	return TRUE;            //返回TRUE,表示成功执行本函数
}
#endif