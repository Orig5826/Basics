
#ifndef _USB_HID_H_
#define _USB_HID_H_

#include <windows.h>

typedef struct _HID_Config
{
	USHORT PID;
	USHORT VID;
}HID_Config;

//GETSTRING参数
#define GET_MANUFACTURE		1	/**< 厂商信息 */
#define GET_PRODUCT			2	/**< 产品信息 */
#define GET_SERIALNUM		3	/**< 序列号 */

//
// \breaf HID指定设备连接
// 参数若为NULL，则使用默认参数
//
__declspec(dllexport) BOOL USB_HID_Connect(HID_Config * hid_cfg);
__declspec(dllexport) void USB_HID_Close(void);
__declspec(dllexport) BOOLEAN USB_HID_Write(unsigned char ReportID, unsigned char * sBuf, unsigned int sLen);
__declspec(dllexport) BOOLEAN USB_HID_Read(unsigned char ReportID, unsigned char * rBuf, unsigned int * rLen);
__declspec(dllexport) BOOLEAN USB_HID_GetString(unsigned char * rBuf, unsigned int rLen, unsigned char infotype);
__declspec(dllexport) void usb_hid_test(void);


#endif