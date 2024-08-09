
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

#include "common.h"


// -------------------------------------------------
GUID GUID_USBDISK = { 0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b };
GUID GUID_USBCDROM = { 0x53f56308L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b};


#define SPT_SENSE_LENGTH 32					//!< 
#define SPTWB_DATA_LENGTH (65536 + 16)		//!< 数据发送接收缓存大小,默认64k+
											//!< 多余的空间是为了留有余量，防溢出

/*
 * 文件作用域变量
 */
static HANDLE usb_dev_handle[256];
static char usb_dev_symbolic[256][32];

/*
 *	函数声明
 */
static BOOL usb_scsi_cmd(HANDLE hDevHandle, UCHAR Direction, PUCHAR pData, DWORD Data_Length, PUCHAR CB, UCHAR CBLength, PUCHAR resData, PDWORD resLen);

/*
 * 打印错误码
 */
static void FormatErrorCode(void)
{
	char szBuf[128];
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
		"[ErrorCode = %d]: %s",
		ErrorCode, (char *)lpMsgBuf);

	DBG(szBuf);

	LocalFree(lpMsgBuf);
}


static int GetDevicePath(int num, LPTSTR path, GUID guid)
{
	HDEVINFO hardwareDeviceInfo;
	SP_INTERFACE_DEVICE_DATA deviceInfoData;
	int result;
	ULONG requiredLength;
	ULONG predictedLength;
	PSP_INTERFACE_DEVICE_DETAIL_DATA functionClassDeviceData;

	hardwareDeviceInfo = SetupDiGetClassDevs(
		&guid,
		NULL, // Define no enumerator (global)
		NULL, // Define no
		(DIGCF_PRESENT | // Only Devices present
		DIGCF_INTERFACEDEVICE)); // Function class devices.

	deviceInfoData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

	result = SetupDiEnumDeviceInterfaces(hardwareDeviceInfo,
		0, // We don't care about specific PDOs
		&guid,
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
	HANDLE hDevHandle = INVALID_HANDLE_VALUE;
	char DevPath[256];

	// 必须保证长度正确
	if (Len > 28)
	{
		DBG("The Length of SymLink Is Overflow!\n");
		goto find_exit;
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
		rv = GetDevicePath(i, DevPath, GUID_USBDISK);
		if (!rv)
		{
			rv = GetDevicePath(i, DevPath, GUID_USBCDROM);
			if (!rv)
			{
				DBG("Can't Find the Device!\n");
				goto find_exit;
			}
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
			DBG("CreateFile Failed!\n");
			DBG(DevPath);
			FormatErrorCode();

			DBG("Maybe：\n"
				"	1.Do Administrator Rights Need?\n"
				"	2.Is the device name correct?\n");
			goto find_exit;
		}

		UCHAR InquiryData[37] = {0};
		DWORD InquiryDataLen = 32;
		UCHAR CB[0x10] = { 0x12,0x00,0x00,0x00,0x24 };
		usb_scsi_cmd(hDevHandle, SCSI_IOCTL_DATA_IN, NULL, 36, CB, 0x06, InquiryData, &InquiryDataLen);

		// 暂不对前8字节进行过滤，因有时存在盘符，有时又不需要盘符。
		//if (0 == memcmp(InquiryData, "\x00\x80\x02\x02\x1f\x00\x00\x00", 8))
		{
			if (0 == memcmp(InquiryData + 8, SymLink, Len))
			{
				DBG("Find the Device: ");
				DBG(SymLink);

				usb_dev_handle[i] = hDevHandle;

				memcpy(usb_dev_symbolic[i], InquiryData + 8, 28);
				usb_dev_symbolic[i][28] = '\0';

				return hDevHandle;
			}
		}
		CloseHandle(hDevHandle);
	}

find_exit:
	return NULL;
}

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
	sptwb.spt.TimeOutValue = 10;
	sptwb.spt.DataIn = Direction;
	// Data
	sptwb.spt.DataTransferLength = Data_Length;
	if (Data_Length > SPTWB_DATA_LENGTH)
	{
		DBG("Buffer overflow!\n");
		return FALSE;
	}

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
		DBG("DeviceIoControl Error!\n");
		FormatErrorCode();
		status = FALSE;
	}
	else
	{
		switch (Direction)
		{
		case SCSI_IOCTL_DATA_IN:
			memcpy(resData, sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
			*resLen = sptwb.spt.DataTransferLength;
			break;
		case SCSI_IOCTL_DATA_OUT:
			*resLen = 0;
		case SCSI_IOCTL_DATA_UNSPECIFIED:
			//DBG_LOG("\n");
			break;
		default:
			break;
		}
		status = TRUE;
	}
	return status;
}

HANDLE DLL_API usb_open(uint8_t* symbolic_link)
{
	HANDLE handle = NULL;
	int length;

	length = (int)strlen(symbolic_link);
	handle = usb_find(symbolic_link, length);
	if (handle != NULL)
	{
		DBG("---------------- Open USB Device ----------------\n");
	}
	return handle;
}

BOOL DLL_API usb_close(HANDLE handle)
{
	if (FALSE == CloseHandle(handle))
	{
		DBG("Close USB Failed!\n");
		FormatErrorCode();
		return FALSE;
	}
	else
	{
		DBG("---------------- Close USB Device ----------------\n");
	}
	return TRUE;
}

BOOL DLL_API usb_write(HANDLE handle, uint8_t * cmd, uint8_t cmd_len, uint8_t * sBuf, uint32_t sLen)
{
	uint32_t rLen = 0;			//此处无用，仅仅是为了函数参数的调用
	uint8_t CB[31] = {0xff};	//默认第一个字节为0xFF，但是现在可以在外部修改了
	uint32_t i = 0;

	if (cmd_len > 16)
	{
		return FALSE;
	}
	memcpy(CB, cmd, cmd_len);

	if (TRUE != usb_scsi_cmd(handle, SCSI_IOCTL_DATA_OUT, sBuf, sLen, CB, cmd_len, NULL, &rLen))
	{
		return FALSE;
	}

	for (i = 0; i < 256; i++)
	{
		if (handle == usb_dev_handle[i])
		{
			break;
		}
	}
	if (i != 256)
	{
		// DBG_LOG("CB=", CB, cmd_len);
		DBG_LOG("->", sBuf, sLen);
	}

	return TRUE;
}

BOOL DLL_API usb_read(HANDLE handle, uint8_t * cmd, uint8_t cmd_len, uint8_t * rBuf, uint32_t * rLen)
{
	BOOL ret = FALSE;
	UCHAR CB[31] = { 0xfe };
	if (cmd_len > 16)
	{
		return FALSE;
	}
	memcpy(CB, cmd, cmd_len);

	ret = usb_scsi_cmd(handle, SCSI_IOCTL_DATA_IN, NULL, *rLen, CB, cmd_len, rBuf, (PDWORD)rLen);
	if (ret != FALSE)
	{
		// DBG_LOG("CB=", CB, cmd_len);
		DBG_LOG("<-", rBuf, *rLen);
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