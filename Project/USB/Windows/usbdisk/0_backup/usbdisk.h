#ifndef _USBDISK_H_
#define _USBDISK_H_

#undef UNICODE

#include <stdint.h>
#include <Windows.h>

#ifdef DLL_EXPORTS
#define DLL_API  _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif

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

typedef BOOL bool;

// 打开设备 
DLL_API bool CALL usb_open(PUCHAR symbolic_link);
// 关闭设备
DLL_API void CALL usb_close(void);
// 数据读写接口 
DLL_API bool CALL usb_write(uint8_t * cmd, uint8_t cmd_len, uint8_t * sBuf, uint32_t sLen);
DLL_API bool CALL usb_read(uint8_t * cmd, uint8_t cmd_len, uint8_t * rBuf, uint32_t * rLen);


// 显示数据
DLL_API void CALL usb_display(PUCHAR buffer, DWORD size);
// 配置Debug信息的详细等级
// 0.仅显示底层信息
// 1.基本信息，write&read
// 2.在1基础上附件assic显示信息
DLL_API void CALL usb_set_debug_level(uint8_t debug_level);
// 读取版本号
DLL_API char*  CALL get_version(void);


#endif
