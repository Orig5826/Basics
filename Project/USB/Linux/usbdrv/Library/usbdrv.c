
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libusb.h>
//
#include "usbdrv.h"

// --------------------------------------------
static libusb_device_handle * s_Handle;
//static uint8_t s_UsbType = USB_SCSI;
static uint8_t usbdrv_debug_level = 1;

static uint8_t s_endpoint_out = EP_OUT_DEFAULT;
static uint8_t s_endpoint_in = EP_IN_DEFAULT;

// --------------------------------------------
static void usb_display(uint8_t * buffer,uint32_t size)
{
	unsigned i, j, k;
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
		if(i + 16 < size)
		{
			printf("\n\t");
		}
		else
		{
			printf("\n");
		}
	}
}

bool usb_open(uint16_t vid, uint16_t pid)
{
	libusb_device_handle * handle;
	int r = 0;

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
	printf("---------------- START ----------------\n");
	return True;
}

void usb_close()
{
	libusb_release_interface(s_Handle,0);
	libusb_close(s_Handle);
	libusb_exit(NULL);
	printf("---------------- END ----------------\n");
}

void usb_set_endpoint(uint8_t outpoint,uint8_t inpoint)
{
	s_endpoint_in = inpoint;
	s_endpoint_out = outpoint;
}

void usb_set_debug_level(uint8_t debug_level)
{
	usbdrv_debug_level = debug_level;
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

static uint8_t usb_scsi_send_cbw(uint8_t endpoint,uint8_t direction,uint32_t length_expect,
				uint8_t CBLength,uint8_t * CB,uint32_t * tag_ret)
{
	static uint32_t tag = 0x01;
	int i,r,size;
	SCSI_CBW cbw;
	memset((uint8_t *)&cbw,0x00,sizeof(cbw));

	cbw.dCBWSignature = 0x43425355;
	cbw.dCBWDataTransferLength = length_expect;
	* tag_ret = tag;
	cbw.dCBWTag = tag++;
	cbw.bmCBWFlags = direction;
	// 自定义命令
	if(CBLength == 0 || CBLength > 16)
	{
		return -1;
	}
	if(CB == NULL)
	{
		return -1;
	}
	cbw.bCBWCBLength = CBLength;
	for(i= 0; i < CBLength; i ++)
	{
		cbw.CBWCB[i] = CB[i];
	}

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
		return -1;
	}
	return 0;
}

static uint8_t usb_scsi_get_status(uint8_t endpoint, uint32_t expected_tag)
{
	int i,size,r;
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
	int size,i,r;
	uint8_t CBLength = 0x01,CB = 0xFF;
	usb_scsi_send_cbw(s_endpoint_out,0x00,sLen,CBLength,&CB,&tag);
	// ----------------------------------------------
	// 发送数据
	i = 0;
	do {
		r = libusb_bulk_transfer(s_Handle, s_endpoint_out,sBuf, sLen, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, s_endpoint_out);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));
	if (r != LIBUSB_SUCCESS) {
		printf("usb_write: %s\n", libusb_strerror((enum libusb_error)r));
		return False;
	}

	// ----------------------------------------------
	if(0 != usb_scsi_get_status(s_endpoint_in,tag))
	{
		return False;
	}

	if(usbdrv_debug_level >=1 )
	{
		printf("[OUT]");
		usb_display(sBuf,sLen);
	}

	return True;
}

bool usb_read(uint8_t * rBuf,uint32_t * rLen)
{
	uint32_t tag;
	int r,size,i;
	uint8_t CBLength = 0x01,CB = 0xFF;
	usb_scsi_send_cbw(s_endpoint_out,0x80,* rLen,CBLength,&CB,&tag);
	// ----------------------------------------------
	// 接收数据
	i = 0;
	do {
		r = libusb_bulk_transfer(s_Handle, s_endpoint_in,rBuf,*rLen, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, s_endpoint_in);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));
	if (r != LIBUSB_SUCCESS) {
		printf("usb_read: %s\n", libusb_strerror((enum libusb_error)r));
		return False;
	}
	// ----------------------------------------------
	if(0 != usb_scsi_get_status(s_endpoint_in,tag))
	{
		return False;
	}
	*rLen = size;

	if(usbdrv_debug_level >=1 )
	{
		printf("[IN]");
		usb_display(rBuf,*rLen);
	}

	return True;
}


bool usb_write_hs(uint8_t * apdu,uint8_t apdu_len,uint8_t * sBuf,uint32_t sLen)
{
	uint32_t tag;
	int size,i,r;
	uint8_t CBLength,CB[16];
	if(apdu_len > 15)
	{
		return False;
	}
	CBLength = apdu_len + 1;
	CB[0] = 0xfd;
	memcpy(CB + 1,apdu,apdu_len);
	usb_scsi_send_cbw(s_endpoint_out,0x00,sLen,CBLength,CB,&tag);
	// ----------------------------------------------
	// 发送数据
	i = 0;
	do {
		r = libusb_bulk_transfer(s_Handle, s_endpoint_out,sBuf, sLen, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, s_endpoint_out);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));
	if (r != LIBUSB_SUCCESS) {
		printf("usb_write: %s\n", libusb_strerror((enum libusb_error)r));
		return False;
	}

	// ----------------------------------------------
	if(0 != usb_scsi_get_status(s_endpoint_in,tag))
	{
		return False;
	}

	if(usbdrv_debug_level >=1 )
	{
		printf("[OUT]");
		usb_display(sBuf,sLen);
	}

	return True;
}

bool usb_read_hs(uint8_t * apdu,uint8_t apdu_len,uint8_t * rBuf,uint32_t * rLen)
{
	uint32_t tag;
	int r,size,i;
	uint8_t CBLength,CB[16];
	if(apdu_len > 15)
	{
		return False;
	}
	CBLength = apdu_len + 1;
	CB[0] = 0xfe;
	memcpy(CB + 1,apdu,apdu_len);
	usb_scsi_send_cbw(s_endpoint_out,0x80,* rLen,CBLength,CB,&tag);
	// ----------------------------------------------
	// 接收数据
	i = 0;
	do {
		r = libusb_bulk_transfer(s_Handle, s_endpoint_in,rBuf,*rLen, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(s_Handle, s_endpoint_in);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));
	if (r != LIBUSB_SUCCESS) {
		printf("usb_read: %s\n", libusb_strerror((enum libusb_error)r));
		return False;
	}
	// ----------------------------------------------
	if(0 != usb_scsi_get_status(s_endpoint_in,tag))
	{
		return False;
	}
	*rLen = size;

	if(usbdrv_debug_level >=1 )
	{
		printf("[IN]");
		usb_display(rBuf,*rLen);
	}

	return True;
}


#if 0
int main()
{
	uint8_t data[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};\
	uint8_t rBuf[8];
	uint32_t rLen = 8;
	if(False == usb_open(0x2309,0x0606))
	{
		return -1;
	}

	for(int i = 0; i < 10; i++)
	{
		usb_write(data,0x08);
		usb_read(rBuf,&rLen);
	}

	usb_close();
}
#endif