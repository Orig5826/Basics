#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
	注意：该头文件不再单独复制出来，直接使用了
	usbdisk的头文件
*/
#include "usbdisk.h"
#pragma comment(lib,"usbdisk.lib")

void default_test();
void apdu_test();

void __cdecl main()
{
	apdu_test();
	// 等待按键退出...
	system("pause");
}

// ---------------------------------------------------------------
void default_test()
{
	uint8_t apdu[5] = { 0x00,0x84,0x00,0x00,0x08 };
	uint8_t sBuf[32] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };
	uint8_t rBuf[32];
	uint32_t rLen = 32;

	if (FALSE == usb_open())
	{
		printf("设备打开失败");
		exit(-1);
	}
	//usb_set_debug_level(2);
	//
	usb_write(sBuf, 32);
	//
	memset(rBuf, 0x00, sizeof(rBuf));
	usb_read(rBuf, &rLen);

	usb_write_hs(apdu, 5, sBuf, 32);
	usb_read_hs(apdu, 5, rBuf, &rLen);

	usb_close();
}

// ---------------------------------------------------------------
#define BUFFER_SIZE_MAX	(0x400+0x40+8)	///< 当前发送和接受的数据的最大个数

static uint8_t SendBuffer[BUFFER_SIZE_MAX];	///< 发送缓存区
static uint8_t RecvBuffer[BUFFER_SIZE_MAX];
static uint32_t SendLength;
static uint32_t RecvLength;

static BOOL SendAPDU(uint8_t CLA, uint8_t INS, uint8_t P1, uint8_t P2, uint32_t Lc, uint8_t* data, uint32_t Le)
{
	// 暂定长度字段（Le,Lc）都为1个字节，因为目前没有发送太长的数据
	memset(SendBuffer, 0x00, BUFFER_SIZE_MAX);
	memset(RecvBuffer, 0x00, BUFFER_SIZE_MAX);
	SendLength = 0;
	RecvLength = BUFFER_SIZE_MAX;
	SendBuffer[0] = CLA;
	SendBuffer[1] = INS;
	SendBuffer[2] = P1;
	SendBuffer[3] = P2;
	if (Lc == 0x00 && data == NULL && Le == 0x00)
	{
		// CASE1
		SendLength = 4;
	}
	else if (Lc == 0x00 && data == NULL && Le != 0x00)
	{
		//CASE2
		if (Le < 256)
		{
			SendBuffer[4] = Le;
			SendLength = 4 + 1;
		}
		else
		{
			SendBuffer[4] = 0x00;
			SendBuffer[5] = (Le >> 8) & 0xff;
			SendBuffer[6] = Le  & 0xff;
			SendLength = 4 + 3;
		}
	}
	else if (Lc != 0x00 && data != NULL && Le == 0x00)
	{
		if (Lc < 256)
		{
			SendBuffer[4] = Lc;
			memcpy(SendBuffer + 5, data, Lc);
			SendLength = 4 + 1 + Lc;
		}
		else
		{
			SendBuffer[4] = 0x00;
			SendBuffer[5] = (Lc >> 8) & 0xff;
			SendBuffer[6] = Lc  & 0xff;
			memcpy(SendBuffer + 7, data, Lc);
			SendLength = 4 + 3 + Lc;
		}
	}
	else if (Lc != 0x00 && data != NULL && Le != 0x00)
	{
		if (Lc < 256)
		{
			SendBuffer[4] = Lc;
			memcpy(SendBuffer + 5, data, Lc);
			SendLength = 4 + 1 + Lc;
		}
		else
		{
			SendBuffer[4] = 0x00;
			SendBuffer[5] = (Lc >> 8) & 0xff;
			SendBuffer[6] = Lc & 0xff;
			memcpy(SendBuffer + 7, data, Lc);
			SendLength = 4 + 3 + Lc;
		}

		if (Le < 256)
		{
			SendBuffer[SendLength] = Le;
			SendLength = SendLength + 1;
		}
		else
		{
			SendBuffer[SendLength] = 0x00;
			SendBuffer[SendLength + 1] = (Le >> 8) & 0xff;
			SendBuffer[SendLength + 2] = Le & 0xff;
			SendLength = SendLength + 3;
		}
	}
	else
	{
		printf("APDU 参数配置不正确！\n");
		return FALSE;
	}
	// Send APDU
	usb_write(SendBuffer, SendLength);
	usb_read(RecvBuffer, &RecvLength);

	if (RecvBuffer[RecvLength - 2] != 0x90 && RecvBuffer[RecvLength - 1] != 0x00)
	{
		printf("返回非9000的错误，请查找原因\n");
		return FALSE;
	}
	return TRUE;
}

static BOOL GetResponse(uint8_t *response, uint32_t * resLen)
{
	if (RecvLength > 2)
	{
		*resLen = RecvLength - 2;
		memcpy(response, RecvBuffer, *resLen);
	}
	else
	{
		*resLen = 0;
		response = NULL;
	}
}

static BOOL GetStatus(uint8_t SW[2])
{
	SW[0] = RecvBuffer[RecvLength - 2];
	SW[1] = RecvBuffer[RecvLength - 1];
}
void apdu_test()
{
	clock_t start,end;
	uint8_t data[1024] = { 0 };
	if (FALSE == usb_open())
	{
		printf("设备打开失败");
		exit(-1);
	}

	start = clock();

	SendAPDU(0x00, 0x84, 0x00, 0x00, 0, NULL, 1024);

	// 加密
	// SendAPDU(0x00, 0x41, 0x00, 0xff, 1024, data, 1024 + 8);

	end = clock();
	printf("计时: %fs\n",(double)(end - start)/ CLK_TCK);
	usb_close();
}