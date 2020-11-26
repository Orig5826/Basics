#ifndef _COMMON_H_
#define _COMMON_H_

#undef UNICODE

#include <stdint.h>
#include "usbdisk.h"

#ifdef _DEBUG
/**
 * 2019.5.13 ���ֺ���ֵ�����
 * usb_display()��usbdisk_debug_level>=2��ʱ��
 * ��������odprintf�����У���֪��Ϊʲô
 * �޸�Ϊ������odprintf����ʹ��OutputDebugString
 * �Ҹ��˾��ã�odprintf�����е�ʵ�ֿ��ܻ�����һ����bug
 * ��Ȼ����ʹ�õ���˵������������Ѿ�ʹ���˺ö�����
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
