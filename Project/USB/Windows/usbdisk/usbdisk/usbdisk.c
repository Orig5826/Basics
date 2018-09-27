
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


/*
* SymLink 长度必须为36-4-4 = 28字节
* 其中VID占8字节，PID占16字节，Version（n.nn）占4字节
*/
static HANDLE usb_find(char * SymLink)
{
	HANDLE hDevHandle = NULL;
	char DevPath[10];

	for (char c = 'C'; c < 'Z'; c++)
	{
		sprintf(DevPath, "\\\\.\\%c:", c);
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
			printf("设备打开失败\n");
			FormatErrorCode();
			goto Exit;
		}

		UCHAR InquiryData[36];
		DWORD InquiryDataLen = 32;
		UCHAR CB[0x10] = { 0x12,0x00,0x00,0x00,0x24 };
		usb_scsi_cmd(hDevHandle, SCSI_IOCTL_DATA_IN, NULL, 36, CB, 0x06, InquiryData, &InquiryDataLen);
		if (InquiryDataLen != 36)
		{
			printf("InquiryDataLen -> Error!\n");
		}
		if (0 == memcmp(InquiryData, "\x00\x80\x02\x02\x1f\x00\x00\x00", 8))
		{
			if (0 == memcmp(InquiryData + 8, SymLink, 28))
			{
				printf("找到设备: [%s]\n", SymLink);
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
		if (usbdisk_debug_level == 0)
		{
			printf("[CMD]:0x%02x\n", CB[0]);
		}
		switch (Direction)
		{
		case SCSI_IOCTL_DATA_IN:
			if (usbdisk_debug_level == 0)
			{
				printf("\t\t[IN]:\n");
				usb_display(sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
			}
			memcpy(resData, sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
			*resLen = sptwb.spt.DataTransferLength;
			break;
		case SCSI_IOCTL_DATA_OUT:
			if (usbdisk_debug_level == 0)
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
void usb_display(PUCHAR buffer, DWORD size)
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

bool usb_open(void)
{
	s_Handle = usb_find(SYMBOLIC_LINK);
	if (s_Handle == NULL)
	{
		printf("设备打开失败\n");
		return FALSE;
	}
	return TRUE;
}

void usb_close(void)
{
	CloseHandle(s_Handle);
}

void usb_set_debug_level(uint8_t debug_level)
{
	usbdisk_debug_level = debug_level;
}

bool usb_write(uint8_t * sBuf, uint32_t sLen)
{
	DWORD rLen = 0;		//此处无用，仅仅是为了函数参数的调用
	UCHAR CB[31] = {0xff};
	if (usbdisk_debug_level >= 1)
	{
		printf("[OUT]:\n");
		usb_display(sBuf, sLen);
	}
	return usb_scsi_cmd(s_Handle, SCSI_IOCTL_DATA_OUT, sBuf, sLen, CB, 1, NULL, &rLen);
}
bool usb_read(uint8_t * rBuf, uint32_t * rLen)
{
	BOOL ret = FALSE;
	UCHAR CB[31] = { 0xff };

	ret = usb_scsi_cmd(s_Handle, SCSI_IOCTL_DATA_IN, NULL, *rLen, CB, 1, rBuf, (PDWORD)rLen);
	if (ret != FALSE)
	{
		if (usbdisk_debug_level >= 1)
		{
			printf("[IN]:\n");
			usb_display(rBuf,*rLen);
		}
	}
	return ret;
}

bool usb_write_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * sBuf, uint32_t sLen)
{
	DWORD rLen = 0;		//此处无用，仅仅是为了函数参数的调用
	UCHAR CB[31] = { 0xfd };
	if (apdu_len > 15)
	{
		return FALSE;
	}
	memcpy(CB + 1, apdu, apdu_len);

	if (usbdisk_debug_level >= 1)
	{
		printf("[OUT]:\n");
		usb_display(sBuf, sLen);
	}
	return usb_scsi_cmd(s_Handle, SCSI_IOCTL_DATA_OUT, sBuf, sLen, CB, apdu_len + 1, NULL, &rLen);
}
bool usb_read_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * rBuf, uint32_t * rLen)
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
		if (usbdisk_debug_level >= 1)
		{
			printf("[IN]:\n");
			usb_display(rBuf, *rLen);
		}
	}
	return ret;
}
