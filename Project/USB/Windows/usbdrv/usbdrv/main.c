#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "typedef.h"
#include "usbdrv.h"

#include <Windows.h>
#include <setupapi.h>
#include <usbspec.h>


#define GUID_MSD_STR	"{ABB9810B - ED61 - 4A29 - A3DC - AA719073FCBF}"


#if 1
int main()
{
	UsbDrv_OpenDevice(0x2309, 0x0606);

}
#else
int main(int argc, char * argv[])
{
	HANDLE hDevHandle;
	HKEY hKey;
	LONG retStatus;
	DWORD Count;
	DWORD dwType;
	DWORD dwSize;
	WCHAR * RegKey[10] = { L"0",L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9" };	//��֪�������Ǹ�10�˻���a�ˣ�
	char lszValue[255];
	char * p = lszValue + 4;
	WCHAR UsbDevPath[256] = L"\\\\?\\usb#vid_090c&pid_1000#5&2330cd79&0&5#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";

	retStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum"),
		0L,
		KEY_READ,        //Changed from v1.0.  Used to be "KEY_ALL_ACCESS" which requires administrator logon (and application administrator execution level to work in Vista).
		&hKey);
	if (retStatus != ERROR_SUCCESS)
	{
		printf("RegOpenKeyEx����ʧ��,retStatus =  0x%08x\n", retStatus);
		return -1;
	}

	printf("Waiting the Device plug in ...\n");
	while (1)
	{
		retStatus = RegQueryValueEx(hKey,
			TEXT("Count"),
			NULL,
			&dwType,
			(LPBYTE)&lszValue,
			&dwSize);
		if (retStatus != ERROR_SUCCESS)
		{
			printf("RegQueryValueEx����ʧ��,retStatus =  0x%08x\n", retStatus);
		}
		Count = *((DWORD *)&lszValue[0]);
		if (Count != 0)
		{
			printf("RegQueryValueEx : Count = %d\n", Count);
			break;
		}
		else
		{
			continue;
		}
	}
	if (Count >= 10)
	{
		printf("������豸̫�࣬����ʶ��\n");
		return -1; 
	}

	for (DWORD i = 0; i < Count; i++)
	{
		dwType = REG_SZ;
		dwSize = 256;
		printf("RegKey = %ls\n", RegKey[i]);
		retStatus = RegQueryValueEx(hKey,
			TEXT("0"),
			NULL,
			&dwType,
			(LPBYTE)&lszValue,
			&dwSize);
		if (retStatus != ERROR_SUCCESS)
		{
			printf("RegQueryValueEx����ʧ��,retStatus =  0x%08x\n", retStatus);
			return -1;
		}

		printf("lszValue = %ls\n", (LPCWSTR)&lszValue);
		for (DWORD i = 0; i < dwSize; i++)
		{
			if (lszValue[i] != '\0')
			{
				if (lszValue[i] == '\\')
				{
					UsbDevPath[4 + i/2] = '#';
				}
				else
				{
					UsbDevPath[4 + i/2] = lszValue[i];
				}
			}
		}
		printf("DevPath = %ls\n",UsbDevPath);
		hDevHandle = CreateFile(UsbDevPath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL);

		if (hDevHandle != INVALID_HANDLE_VALUE)
		{
			printf("--> �豸�򿪳ɹ�\n");
		}
		else
		{
			printf("--> �豸��ʧ�� ErrorCode = 0x%08x\n",GetLastError());
			return -1;
		}
	}

	{
		char rBuf[128];
		DWORD rLen = 0;
		// ��ȡ���̵���Ϣ
		if (!DeviceIoControl(hDevHandle,
			IOCTL_STORAGE_GET_MEDIA_SERIAL_NUMBER,
			NULL, 0,
			rBuf, sizeof(rBuf),
			&rLen,
			NULL))
		{
			printf("��ȡ���к�ʧ��,ErrorCode = 0x%08x\n",GetLastError());
			return -1;
		}
		else
		{
			printf("��ȡ���кųɹ���rLen = %d\n",rLen);
			for (DWORD i = 0; i < rLen; i++)
			{
				printf("%02x ", rBuf[i]);
			}
		}
	}


	CloseHandle(hDevHandle);
	system("pause");
	return 0;
}

#endif