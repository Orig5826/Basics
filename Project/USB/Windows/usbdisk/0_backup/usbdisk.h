#ifndef _USBDISK_H_
#define _USBDISK_H_

#undef UNICODE

#include <stdint.h>
#include <Windows.h>

/*
__cdecl
	C/C++Ĭ�ϵ��÷�ʽ���������ҵ���ѹջ���������������ջ���ɵ����߸�������
	һ������printf���������������
__stdcall
	Pascal����Ĭ�ϵ��÷�ʽ��ͨ������Win32 API�У��������ô��ҵ����ѹջ��ʽ��
	���������޸Ķ�ջ���������Զ���ǰ�����»��ߣ��������һ��@���ţ��������Ų����ĳߴ�

����û�в���������������£�һ�㶼ʹ��__stdcall
*/
#define CALL	__stdcall

#ifdef DLL_EXPORTS
#define DLL_DEF  _declspec(dllexport)
#else
#define DLL_DEF _declspec(dllimport)
#endif


#define DLL_API  DLL_DEF CALL

// ------------------------------------------------
// ���豸 
HANDLE DLL_API usb_open(uint8_t* symbolic_link);
// �ر��豸
BOOL DLL_API usb_close(HANDLE handle);
// ���ݶ�д�ӿ� 
BOOL DLL_API usb_write(HANDLE handle, uint8_t* cmd, uint8_t cmd_len, uint8_t* sBuf, uint32_t sLen);
BOOL DLL_API usb_read(HANDLE handle, uint8_t* cmd, uint8_t cmd_len, uint8_t* rBuf, uint32_t* rLen);

#endif
