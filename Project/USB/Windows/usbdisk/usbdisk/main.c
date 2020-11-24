#ifndef _WINDLL

#include <stdint.h>
#include <stdio.h>

#include "usbdisk.h"
#include "common.h"


#define SYMBOLIC_LINK_2	"HSEC    usb2uart_c1test 0002"
#define SYMBOLIC_LINK_3	"HSEC    usb2uart_c1test 0003"

typedef struct _param_t
{
	uint8_t* symbolic;
	uint32_t delay_ms;
}param_t;

static HANDLE h_mutex = NULL;

void usb_write_ff(HANDLE handle,uint8_t* data, uint32_t len)
{
	uint8_t cmd[16] = { 0xff };
	usb_write(handle, cmd, 1, data, len);
}

void usb_read_ff(HANDLE handle, uint8_t* data, uint32_t* len)
{
	uint8_t cmd[16] = { 0xff };
	usb_read(handle, cmd, 1, data, len);
}

void usb_test(param_t *param)
{
	uint8_t cmd_get_random[5] = { 0x00,0x84,0x00,0x00,0x10 };
	uint8_t cmd_get_ver[5] = { 0x00,0xF0,0x00,0x00,0x04 };
	uint8_t res[128];
	uint32_t len = 128;
	HANDLE handle;

	handle = usb_open(param->symbolic);
	if (handle == FALSE)
	{
		printf("设备打开失败");
		exit(-1);
	}

	while (1)
	{
		WaitForSingleObject(h_mutex, INFINITE);

		usb_write_ff(handle,cmd_get_ver, sizeof(cmd_get_random));
		usb_read_ff(handle,res, &len);

		ReleaseMutex(h_mutex);

		Sleep(param->delay_ms);
	}

	usb_close(handle);
}

void main()
{
	HANDLE t1, t2;
	DWORD tid1, tid2;
	param_t param1, param2;
	{
		param1.symbolic = SYMBOLIC_LINK_2;
		param1.delay_ms = 2000;

		param2.symbolic = SYMBOLIC_LINK_3;
		param2.delay_ms = 3000;
	}

	h_mutex = CreateMutex(NULL, FALSE, "mutex");

	t1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)usb_test, (void*)&param1, 0, &tid1);
	t2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)usb_test, (void*)&param2, 0, &tid2);
	Sleep(10000);
}

#endif
