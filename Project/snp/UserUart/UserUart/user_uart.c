// UserDll.cpp : Defines the entry point for the DLL application.
//
#include "tchar.h"
#include "uart.h"
#include "user_uart.h"

// #pragma comment (lib, "usbdisk.lib")

// #define SYMBOLIC_LINK	"HSEC    hsc32k1_usb2sti 1.00"
#define SYMBOLIC_LINK	"ORIG    COM1 [55...AA]  1.00"

#define		DLLEXPORT		_declspec(dllexport) __stdcall

DWORD DLLEXPORT
User_ListDevs			(	OUT TCHAR *pszDrives,	IN OUT DWORD *pulDrivesLen,	OUT DWORD *pulDriveNum )
{
	TCHAR *p = pszDrives;

	_tcscpy( pszDrives, _T(SYMBOLIC_LINK) );
	pszDrives += _tcslen( _T(SYMBOLIC_LINK) );
	pszDrives++;

	*pulDriveNum = 1;
	*pulDrivesLen = 32;// (pszDrives - p) / sizeof(TCHAR);

	return 0;
}

DWORD DLLEXPORT
User_ConnectDev			(	IN TCHAR *pszDrive,	OUT HANDLE *phDevice)
{
	*phDevice = ( HANDLE )0x01;

	if (TRUE != uart_open(1))
	{
		return -1;
	}
	return 0;
}

DWORD DLLEXPORT
User_DisconnectDev		(	IN HANDLE hDevice)
{
	uart_close();
	return 0;
}

DWORD DLLEXPORT
User_ResetCard			(	IN HANDLE hDevice,	OUT BYTE *pbAtr,	IN OUT DWORD *pulAtrLen)
{
	pbAtr[ 0 ] = 0x3b;
	pbAtr[ 1 ] = 0x00;
	*pulAtrLen = 2;

	return 0;
}

DWORD DLLEXPORT
User_PPS				(	IN HANDLE hDevice,	IN OUT BYTE *PPS, IN OUT DWORD *ppsLen )
{
	return 0;
}

DWORD DLLEXPORT
User_Transmit			(	IN HANDLE hDevice,	IN BYTE *pbCommand,	IN DWORD ulCommandLen,	OUT BYTE *pbOutData,	IN OUT DWORD *pulOutDataLen )
{
	if (TRUE != uart_write(pbCommand, ulCommandLen))
	{
		return -1;
	}

	// 允许的缓存Buf大小为1k
	*pulOutDataLen = 1023;
	if (TRUE != uart_read(pbOutData, (uint32_t *)pulOutDataLen))
	{
		return -1;
	}

	if (*pulOutDataLen < 2 || *pulOutDataLen > 1023)
	{
		pbOutData[0] = 0x55;
		pbOutData[1] = 0xAA;
		*pulOutDataLen = 2;
	}

#if 0
	pbOutData[0] = 0x90;
	pbOutData[1] = 0x00;
	*pulOutDataLen = 2;
#endif

	return 0;
}
