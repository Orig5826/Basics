#ifndef _USBDRV_H_
#define _USBDRV_H_

// --------------------------------------------
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef enum _bool
{
	False = 0,
	True = !False
}bool;

// --------------------------------------------
#define USB_DEBUG
// 
#define USB_HID		0
#define USB_SCSI	1
#define USB_CCID	2

#define EP_IN	0x81
#define EP_OUT	0x02
// --------------------------------------------
bool usb_open(uint16_t vid, uint16_t pid);
void usb_close();
bool usb_write(uint8_t * sBuf,uint32_t sLen);
bool usb_read(uint8_t * rBuf,uint32_t * rLen);

#endif
