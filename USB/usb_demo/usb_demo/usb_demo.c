
#include <stdio.h>
#include <stdlib.h>
#include "usb_demo.h"
#include "usb_drive.h"

#define GET_STR_DISP(x) {\
len = sizeof(str);\
USB_HID_GetString(str, len, ##x);\
printf("["#x"]:\n\t\t%S\n",(PWSTR)str); /* %S 似乎是windows上用于显示wchar_t的*/ \
}

void Display(unsigned char * data, unsigned int len)
{
	for (unsigned int i = 0; i < len; i++)
	{
		if (i != 0 && i % 16 == 0)
		{
			printf("\n");
		}
		printf("%02x ", *(data + i));
	}
	printf("\n");
}

int _cdecl main()
{
	unsigned char sBuf[0x40];
	unsigned int sLen = 0;
	unsigned char rBuf[0x40];
	unsigned int rLen = 0;
	unsigned char str[64];
	unsigned int len = 0;
	int i = 0;
	unsigned short num = 0x00;

	usb_hid_test();

	HID_Config hid_cfg;
	hid_cfg.PID = 0x5750;
	hid_cfg.VID = 0x0483;

	if (TRUE == USB_HID_Connect(NULL))
	{
		// 获取厂商信息
		GET_STR_DISP(GET_MANUFACTURE);
		// 获取产品
		GET_STR_DISP(GET_PRODUCT);
		// 获取序列号
		GET_STR_DISP(GET_SERIALNUM);

		while (1)
		{
			for (i = 0; i < 64; i++)
			{
				sBuf[i] = (unsigned char)(num + i) & 0xff;
			}

			sLen = 0x40;
			USB_HID_Write(0, sBuf, sLen);
			rLen = 0x40;
			USB_HID_Read(0, rBuf, &rLen);

			printf("[Read] \n");
			Display(rBuf, rLen);

			if (0 != memcmp(sBuf, rBuf, sLen))
			{
				printf("[Write] \n");
				Display(sBuf, sLen);
				printf("[ERROR] --- 读写不一致 ---\n\n");
				break;
			}

			Sleep(1000);
			num++;
			printf("------------------------\n");
		}
	}

	USB_HID_Close();

	system("pause");
	return 0;
}