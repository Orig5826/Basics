#ifndef _USBDISK_H_
#define _USBDISK_H_

#undef UNICODE

#include <stdint.h>
#include <Windows.h>

/*
__cdecl
	C/C++默认调用方式，函数从右到左压栈，函数本身不清理堆栈，由调用者负责清理。
	一般用于printf参数不定长的情况
__stdcall
	Pascal程序默认调用方式，通常用于Win32 API中，函数采用从右到左的压栈方式。
	函数自身修改堆栈。函数名自动加前导的下划线，后面紧跟一个@符号，其后紧跟着参数的尺寸

若在没有不定长参数的情况下，一般都使用__stdcall
*/
#define CALL	__stdcall

#ifdef DLL_EXPORTS
#define DLL_DEF  _declspec(dllexport)
#else
#define DLL_DEF _declspec(dllimport)
#endif


#define DLL_API  DLL_DEF CALL

// ------------------------------------------------
// 打开设备 
HANDLE DLL_API usb_open(uint8_t* symbolic_link);
// 关闭设备
BOOL DLL_API usb_close(HANDLE handle);
// 数据读写接口 
BOOL DLL_API usb_write(HANDLE handle, uint8_t* cmd, uint8_t cmd_len, uint8_t* sBuf, uint32_t sLen);
BOOL DLL_API usb_read(HANDLE handle, uint8_t* cmd, uint8_t cmd_len, uint8_t* rBuf, uint32_t* rLen);

#endif
