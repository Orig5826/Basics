#ifndef _USBDISK_H_
#define _USBDISK_H_

#include <stdint.h>
#include <Windows.h>

typedef BOOL bool;


//#define SYMBOLIC_LINK	"HSEC    USBCOS          1.00"
#define SYMBOLIC_LINK	"HSEC    USBCOS"

// ���豸 
bool usb_open(void);
// �ر��豸
void usb_close(void);
// ��ʾ����
void usb_display(PUCHAR buffer, DWORD size);
// ����Debug��Ϣ����ϸ�ȼ�
// 0.����ʾ�ײ���Ϣ
// 1.������Ϣ��write&read
// 2.��1�����ϸ���assic��ʾ��Ϣ
void usb_set_debug_level(uint8_t debug_level);

// ���ݶ�д�ӿ� 
// CMD = 0xff
bool usb_write(uint8_t * sBuf, uint32_t sLen);
bool usb_read(uint8_t * rBuf, uint32_t * rLen);
// CMD = 0xfd/fe
bool usb_write_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * sBuf, uint32_t sLen);
bool usb_read_hs(uint8_t * apdu, uint8_t apdu_len, uint8_t * rBuf, uint32_t * rLen);

#endif