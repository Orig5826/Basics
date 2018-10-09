#ifndef _USBDISK_H_
#define _USBDISK_H_

#include <stdint.h>
#include <Windows.h>

#ifdef DLL_EXPORTS
	#define DLL_API _declspec(dllexport)
#else
	#define DLL_API _declspec(dllimport)
#endif

typedef BOOL bool;


//#define SYMBOLIC_LINK	"HSEC    USBCOS          1.00"
#define SYMBOLIC_LINK	"HSEC    USBCOS"

// 打开设备 
DLL_API bool usb_open(void);
// 关闭设备
DLL_API void usb_close(void);
// 显示数据
DLL_API void usb_display(PUCHAR buffer, DWORD size);
// 配置Debug信息的详细等级
// 0.仅显示底层信息
// 1.基本信息，write&read
// 2.在1基础上附件assic显示信息
DLL_API void usb_set_debug_level(uint8_t debug_level);

// 数据读写接口 
// CMD = 0xff
DLL_API bool usb_write(uint8_t * sBuf, uint32_t sLen);
DLL_API bool usb_read(uint8_t * rBuf, uint32_t * rLen);
// CMD = 0xfd/fe
DLL_API bool usb_write_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * sBuf, uint32_t sLen);
DLL_API bool usb_read_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * rBuf, uint32_t * rLen);

#endif