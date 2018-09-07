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
// 
#define EP_OUT_DEFAULT	0x01
#define EP_IN_DEFAULT	0x82
//
#define USB_HID		0
#define USB_SCSI	1
#define USB_CCID	2

// --------------------------------------------
bool usb_open(uint16_t vid, uint16_t pid);
void usb_close();
bool usb_write(uint8_t * sBuf,uint32_t sLen);
bool usb_read(uint8_t * rBuf,uint32_t * rLen);
// hs
bool usb_write_hs(uint8_t * apdu,uint8_t apdu_len,uint8_t * sBuf,uint32_t sLen);
bool usb_read_hs(uint8_t * apdu,uint8_t apdu_len,uint8_t * rBuf,uint32_t * rLen);
// 辅助
void usb_set_debug_level(uint8_t debug_level);
void usb_set_endpoint(uint8_t outpoint,uint8_t inpoint);

#endif
