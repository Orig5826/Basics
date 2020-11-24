#ifndef _COMMON_H_
#define _COMMON_H_

#undef UNICODE

#include <stdint.h>
#include "usbdisk.h"

#ifdef _DEBUG
/**
 * 2019.5.13 出现很奇怪的现象
 * usb_display()若usbdisk_debug_level>=2的时候
 * 卡死在了odprintf函数中，不知道为什么
 * 修改为不适用odprintf，而使用OutputDebugString
 * 我个人觉得，odprintf函数中的实现可能还存在一定的bug
 * 虽然网上使用的人说，这个函数他已经使用了好多年了
 */
#define DBG							odprintf  //printf
#define DBG_LOG(format,data,len)	{DBG((format)); dbgview_display_hex((data),(len));}
#else
#define DBG
#define DBG_LOG(format,data,len)
#endif

void __cdecl odprintf(const char *format, ...);
void dbgview_display_hex(uint8_t* buffer, uint32_t size);

#endif
