#include <stdio.h>
#include <stdlib.h>

#include "usbdisk.h"


void __cdecl main()
{
	uint8_t apdu[5] = { 0x00,0x80,0x00,0x00,0x08 };
	uint8_t sBuf[32] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 ,
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };
	uint8_t rBuf[32];
	uint32_t rLen = 32;

	usb_open();
	//usb_set_debug_level(2);
	//
	usb_write(sBuf, 32);
	//
	memset(rBuf, 0x00, sizeof(rBuf));
	usb_read(rBuf, &rLen);

	usb_write_hs(apdu, 5, sBuf, 32);
	usb_read_hs(apdu, 5, rBuf, &rLen);

	system("pause");
	usb_close();
}