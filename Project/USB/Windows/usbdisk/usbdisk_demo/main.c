#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
	ע�⣺��ͷ�ļ����ٵ������Ƴ�����ֱ��ʹ����
	usbdisk��ͷ�ļ�
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
		// default_test()
		// apdu_test();
		// APDU_Test();

		Encrypt_Test();
	}
	else
	{
		printf("�����в�������\n");
	}
	// �ȴ������˳�...
	system("pause");

	return 0;
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
		printf("�豸��ʧ��");
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
