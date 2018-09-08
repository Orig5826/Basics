
#include <windows.h>
#include <SetupAPI.h>
#include <Cfgmgr32.h>

#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>

#include <devioctl.h>
#include <ntddstor.h>
#include <ntddscsi.h>

BOOL usb_scsi_cmd(HANDLE hDevHandle, UCHAR Direction, PUCHAR pData, DWORD Data_Length, PUCHAR CB, UCHAR CBLength);


void  FormatErrorCode(void)
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
		ErrorCode,(char *)lpMsgBuf);
	printf("%s\n", szBuf);

	LocalFree(lpMsgBuf);
}

HANDLE usb_open()
{
	HANDLE hDevHandle = NULL;
	char * DevPath = "\\\\.\\H:";

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

	return hDevHandle;
Exit:
	CloseHandle(hDevHandle);
	printf("----- END -----\n");
	system("pause");
	return NULL;
}

void __cdecl main()
{
	HANDLE hDevHandle;
	hDevHandle = usb_open();
	if (hDevHandle == NULL)
	{
		printf("设备打开失败\n");
		goto Exit;
	}

	UCHAR CB[0x10] = {0x12,0x00,0x00,0x00,0x24};
	usb_scsi_cmd(hDevHandle, SCSI_IOCTL_DATA_IN, NULL, 36,CB,0x06);

	memset(CB, 0x00, 0x10);
	usb_scsi_cmd(hDevHandle, SCSI_IOCTL_DATA_UNSPECIFIED, NULL, 0, CB, 0x06);

Exit:
	CloseHandle(hDevHandle);
	printf("----- END -----\n");
	system("pause");
}


// --------------------------------------------
static void usb_display(PUCHAR buffer, DWORD size)
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


#define SPT_CDB_LENGTH 32
#define SPT_SENSE_LENGTH 32
#define SPTWB_DATA_LENGTH 512
typedef struct _SCSI_PASS_THROUGH_WITH_BUFFERS {
	SCSI_PASS_THROUGH spt;
	ULONG             Filler;      // realign buffers to double word boundary
	UCHAR             ucSenseBuf[SPT_SENSE_LENGTH];
	UCHAR             ucDataBuf[SPTWB_DATA_LENGTH];
} SCSI_PASS_THROUGH_WITH_BUFFERS, *PSCSI_PASS_THROUGH_WITH_BUFFERS;
BOOL usb_scsi_cmd(HANDLE hDevHandle,UCHAR Direction,PUCHAR pData,DWORD Data_Length,PUCHAR CB,UCHAR CBLength)
{
	BOOL status = FALSE;
	SCSI_PASS_THROUGH_WITH_BUFFERS sptwb;
	ULONG length = 0,returned = 0;

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
		sizeof(SCSI_PASS_THROUGH),
		&sptwb,
		length,
		&returned,
		FALSE);
	if (status != TRUE)
	{
		printf("DeviceIoControl 出错！\n");
		FormatErrorCode();
		status =  FALSE;
	}
	else
	{
		printf("CMD = 0x%02x\t\t",CB[0]);
		switch (Direction)
		{
		case SCSI_IOCTL_DATA_IN:
			printf("[IN]:\n");
			usb_display(sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
			break;
		case SCSI_IOCTL_DATA_OUT:
			printf("[OUT]:\n");
			usb_display(sptwb.ucDataBuf, sptwb.spt.DataTransferLength);
		case SCSI_IOCTL_DATA_UNSPECIFIED:
			printf("\n");
			break;
		default:
			break;
		}
		status =  TRUE;
	}
	return status;
}
