
#include "demo.h"
#include <stdio.h>

void default_demo()
{
#define LENGTH 32
	uint8_t data[LENGTH] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
							0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	uint8_t rBuf[LENGTH];
	uint32_t rLen = LENGTH;
	if (False == usb_open(0x2309, 0x0606))
	{
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		usb_write(data, LENGTH);
		usb_read(rBuf, &rLen);
		printf("\n");
	}

	usb_close();
}

void default_demo_hs()
{
	uint8_t apdu[5] = {0x00,0x84,0x00,0x00,0x08};
	uint8_t rBuf[10];
	uint32_t rLen;
	if (False == usb_open(0x2309, 0x0606))
	{
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		rLen = 10;
		usb_read_hs(apdu,5,rBuf, &rLen);
		printf("\n");
	}

	usb_close();
}

int main(int argc, char const *argv[])
{
	hs_demo();
	return 0;
}
