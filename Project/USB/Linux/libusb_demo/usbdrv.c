
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libusb.h"

// --------------------------------------------
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef enum _bool
{
	False = 0,
	True = !False,
}bool;

#define USB_DEBUG
// 
#define USB_HID		0
#define USB_SCSI	1
#define USB_CCID	2

#define EP_IN	0x81
#define EP_OUT	0x02
// --------------------------------------------
static libusb_device_handle * s_Handle;
static uint8_t s_UsbType = USB_SCSI;
// --------------------------------------------
static void usb_display(uint8_t * buffer,uint32_t size)
{
	unsigned i, j, k;
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
		printf(" ");
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
	printf("\n");
}

bool usb_open(uint16_t vid, uint16_t pid)
{
	libusb_device_handle * handle;
	libusb_device **devs;
	int r = 0,cnt = 0;

	// find the device[vid:pid]
	r = libusb_init(NULL);
	if (r < 0)
	{
		printf("USB Init failed!\n");
		return False;
	}

	// open the device[vid:pid]
	handle = libusb_open_device_with_vid_pid(NULL, vid, pid);
	if (handle == NULL)
	{
		printf("Open USB Device[VID=%04x,PID=%04x] Failed!\n",vid,pid);
		return False;
	}

	// libusb_set_auto_detach_kernel_driver
	// 设置自动卸载内核驱动，注意这个函数调用时不会卸载内核驱动，只是做标记。
	// 在调用libusb_claim_interface之前需要手动调用该函数卸载内核驱动
	// 在调用libusb_release_interface的时候自动加载内核驱动
	r = libusb_set_auto_detach_kernel_driver(handle, 1);
	if (r != LIBUSB_SUCCESS) {
		printf("set_auto_detach_kernel_driver Failed.\n");
	}
	r = libusb_claim_interface(handle, 0);
	if (r != LIBUSB_SUCCESS) {
		switch (r)
		{
		case LIBUSB_ERROR_NOT_FOUND:
			printf("the requested interface does not exist\n");
			break;
		case LIBUSB_ERROR_BUSY:
			printf("another program or driver has claimed the interface\n");
			break;
		case LIBUSB_ERROR_NO_DEVICE:
			printf("the device has been disconnected\n");
			break;
		default:
			printf("code on other failure");
			break;
		}
	}

	s_Handle = handle;
	printf("Open USB Device[VID=%04x,PID=%04x] Succeed!\n",vid,pid);
	return True;
}

void usb_close()
{
	libusb_release_interface(s_Handle,0);
	libusb_close(s_Handle);
	libusb_exit(NULL);
}


// -------------------------------------------------------
typedef struct command_block_wrapper {
	uint32_t dCBWSignature;
	uint32_t dCBWTag;
	uint32_t dCBWDataTransferLength;
	uint8_t bmCBWFlags;
	uint8_t bCBWLUN;
	uint8_t bCBWCBLength;
	uint8_t CBWCB[16];
}SCSI_CBW;
typedef struct command_status_wrapper {
	uint32_t dCSWSignature;
	uint32_t dCSWTag;
	uint32_t dCSWDataResidue;
	uint8_t bCSWStatus;
}SCSI_CSW;

static uint8_t usb_scsi_send_cbw(uint8_t endpoint,uint8_t direction,uint32_t length_expect,uint32_t * tag_ret)
{
	static uint32_t tag = 0x01;
	uint32_t i,r,size;
	SCSI_CBW cbw;
	memset((uint8_t *)&cbw,0x00,sizeof(cbw));

	cbw.dCBWSignature = 0x43425355;
	cbw.dCBWDataTransferLength = length_expect;
	* tag_ret = tag;
	cbw.dCBWTag = tag++;
	cbw.bmCBWFlags = direction;
	// 自定义命令
	cbw.bCBWCBLength = 0x01;
	cbw.CBWCB[0] = 0xff;

	do {
		// The transfer length must always be exactly 31 bytes.
		r = libusb_bulk_transfer(s_Handle, endpoint, (unsigned char*)&cbw, 31, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, endpoint);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i < 3));
	if (r != LIBUSB_SUCCESS) {
		printf("usb_scsi_send_cbw failed: %s\n", libusb_strerror((enum libusb_error)r));
		usb_close();
		return -1;
	}
	return 0;
}

static uint8_t usb_scsi_get_status(uint8_t endpoint, uint32_t expected_tag)
{
	uint32_t i,size,r;
	SCSI_CSW csw;

	memset((uint8_t *)&csw,0x00,sizeof(csw));
	i = 0;
	do {
		r = libusb_bulk_transfer(s_Handle, endpoint, (unsigned char*)&csw, 13, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, endpoint);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));

	if (r != LIBUSB_SUCCESS) {
		printf("usb_scsi_get_status: %s\n", libusb_strerror((enum libusb_error)r));
		return -1;
	}
	if (size != 13) {
		printf("usb_scsi_get_status: received %d bytes (expected 13)\n", size);
		return False;
	}
	
	if (csw.dCSWTag != expected_tag) {
		printf(" usb_scsi_get_status: mismatched tags (expected %08X, received %08X)\n",
			expected_tag, csw.dCSWTag);
		return -1;
	}

	//printf("   Mass Storage Status: %02X (%s)\n", csw.bCSWStatus, csw.bCSWStatus?"FAILED":"Success");
	if (csw.bCSWStatus) {
		printf("   Mass Storage Status: %02X (%s)\n", csw.bCSWStatus, csw.bCSWStatus?"FAILED":"Success");
		if (csw.bCSWStatus == 1)
			return -2;
		else
			return -1;
	}
	return 0;
}

bool usb_write(uint8_t * sBuf,uint32_t sLen)
{
	uint32_t tag;
	uint32_t size,i,r;
	usb_scsi_send_cbw(EP_OUT,0x00,sLen,&tag);
	// ----------------------------------------------
	// 发送数据
	i = 0;
	do {
		r = libusb_bulk_transfer(s_Handle, EP_OUT,sBuf, sLen, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, EP_OUT);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));
	if (r != LIBUSB_SUCCESS) {
		printf("usb_write: %s\n", libusb_strerror((enum libusb_error)r));
		usb_close();
		return False;
	}

	// ----------------------------------------------
	if(0 != usb_scsi_get_status(EP_IN,tag))
	{
		return False;
	}

#ifdef USB_DEBUG
	usb_display(sBuf,sLen);
#endif
	return True;
}

bool usb_read(uint8_t * rBuf,uint32_t * rLen)
{
	uint32_t tag,r,size,i;
	usb_scsi_send_cbw(EP_OUT,0x80,* rLen,&tag);
	// ----------------------------------------------
	// 接收数据
	i = 0;
	do {
		r = libusb_bulk_transfer(s_Handle, EP_IN,rBuf,*rLen, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, EP_IN);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));
	if (r != LIBUSB_SUCCESS) {
		printf("usb_read: %s\n", libusb_strerror((enum libusb_error)r));
		return False;
	}
	// ----------------------------------------------
	if(0 != usb_scsi_get_status(EP_IN,tag))
	{
		return False;
	}
	*rLen = size;
#ifdef USB_DEBUG
	usb_display(rBuf,*rLen);
#endif	
	return True;
}

int main()
{
	uint8_t data[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};\
	uint8_t rBuf[8];
	uint32_t rLen = 8;
	if(False == usb_open(0x2309,0x0606))
	{
		return -1;
	}

	usb_write(data,0x08);
	usb_read(rBuf,&rLen);

	usb_close();
}