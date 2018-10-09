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

// ���豸 
DLL_API bool usb_open(void);
// �ر��豸
DLL_API void usb_close(void);
// ��ʾ����
DLL_API void usb_display(PUCHAR buffer, DWORD size);
// ����Debug��Ϣ����ϸ�ȼ�
// 0.����ʾ�ײ���Ϣ
// 1.������Ϣ��write&read
// 2.��1�����ϸ���assic��ʾ��Ϣ
DLL_API void usb_set_debug_level(uint8_t debug_level);

// ���ݶ�д�ӿ� 
// CMD = 0xff
DLL_API bool usb_write(uint8_t * sBuf, uint32_t sLen);
DLL_API bool usb_read(uint8_t * rBuf, uint32_t * rLen);
// CMD = 0xfd/fe
DLL_API bool usb_write_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * sBuf, uint32_t sLen);
DLL_API bool usb_read_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * rBuf, uint32_t * rLen);

#endif