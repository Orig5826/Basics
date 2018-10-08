#ifndef _USBDISK_H_
#define _USBDISK_H_

#include <stdint.h>
#include <Windows.h>

typedef BOOL bool;


//#define SYMBOLIC_LINK	"HSEC    USBCOS          1.00"
#define SYMBOLIC_LINK	"HSEC    USBCOS"

// 打开设备 
bool usb_open(void);
// 关闭设备
void usb_close(void);
// 显示数据
void usb_display(PUCHAR buffer, DWORD size);
// 配置Debug信息的详细等级
// 0.仅显示底层信息
// 1.基本信息，write&read
// 2.在1基础上附件assic显示信息
void usb_set_debug_level(uint8_t debug_level);

// 数据读写接口 
// CMD = 0xff
bool usb_write(uint8_t * sBuf, uint32_t sLen);
bool usb_read(uint8_t * rBuf, uint32_t * rLen);
// CMD = 0xfd/fe
bool usb_write_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * sBuf, uint32_t sLen);
bool usb_read_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * rBuf, uint32_t * rLen);

#endif