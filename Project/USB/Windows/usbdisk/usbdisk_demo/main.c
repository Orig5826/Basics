#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
	注意：该头文件不再单独复制出来，直接使用了
	usbdisk的头文件
*/
#include "usbdisk.h"
#pragma comment(lib,"usbdisk.lib")

#include "apdu.h"
#include "encrypt.h"

void default_test();


int __cdecl main(int argc,char * argv[])
{
	if (argc == 2)
	{
		if (0 == strcmp(argv[1], "0"))
		{
			GenerateKey();
		}
	}
	else if (argc == 1)
	{
		default_test();
		// apdu_test();
		// APDU_Test();

		// Encrypt_Test();
	}
	else
	{
		printf("命令行参数出错！\n");
	}

	// 等待按键退出...
	system("pause");

	return 0;
}

void display_hex(uint8_t* data, uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		printf("%02x ", *(data + i));
	}
	printf("\n");
}

void usb_write_ff(HANDLE handle, uint8_t* data, uint32_t len)
{
	uint8_t cmd[16] = { 0xff };
	usb_write(handle, cmd, 1, data, len);

	display_hex(data, len);
}

void usb_read_ff(HANDLE handle, uint8_t* data, uint32_t* len)
{
	uint8_t cmd[16] = { 0xff };
	usb_read(handle, cmd, 1, data, len);
	
	display_hex(data, *len);
}

void usb_write_hs(HANDLE handle, uint8_t *apdu, uint32_t cmdlen, uint8_t* data, uint32_t len)
{
	uint8_t cmd[16] = { 0xfd };
	memcpy(cmd + 1, apdu, cmdlen);
	usb_write(handle, cmd, 1 + cmdlen, data, len);
}

void usb_read_hs(HANDLE handle, uint8_t * apdu, uint32_t cmdlen, uint8_t* data, uint32_t *len)
{
	uint8_t cmd[16] = { 0xfe };
	memcpy(cmd + 1, apdu, cmdlen);
	usb_read(handle, cmd, 1 + cmdlen, data, len);
}


// ---------------------------------------------------------------
void default_test()
{
	uint8_t apdu[5] = { 0x00,0x84,0x00,0x00,0x10 };
	uint8_t sBuf[32] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };
	uint8_t rBuf[32];
	uint32_t rLen = 32;

	HANDLE handle = NULL;

	handle = usb_open(SYMBOLIC_LINK);
	if (handle == NULL)
	{
		printf("设备打开失败");
		exit(-1);
	}

	//
	usb_write_ff(handle,apdu, 5);
	//
	memset(rBuf, 0x00, sizeof(rBuf));
	usb_read_ff(handle,rBuf, &rLen);

//	usb_write_hs(handle,apdu, 5, sBuf, 32);
//	usb_read_hs(handle,apdu, 5, rBuf, &rLen);

	usb_close(handle);
}
