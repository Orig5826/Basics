#ifndef __USERDISK_H__
#define __USERDISK_H__

#undef UNICODE

#include <stdint.h>
#include <Windows.h>

typedef DWORD ( __stdcall *pUser_ListDevs)			(	OUT TCHAR *pszDrives,	IN OUT DWORD *pulDrivesLen,	OUT DWORD *pulDriveNum );
typedef DWORD ( __stdcall *pUser_ConnectDev)		(	IN TCHAR *pszDrive,	OUT HANDLE *phDevice);
typedef DWORD ( __stdcall *pUser_DisconnectDev)		(	IN HANDLE hDevice);
typedef DWORD ( __stdcall *pUser_ResetCard)			(	IN HANDLE hDevice,	OUT BYTE *pbAtr,	IN OUT DWORD *pulAtrLen);
typedef DWORD ( __stdcall *pUser_PPS)				(	IN HANDLE hDevice,	IN OUT BYTE *PPS, IN OUT DWORD *ppsLen );
typedef DWORD ( __stdcall *pUser_Transmit)			(	IN HANDLE hDevice,	IN BYTE *pbCommand,	IN DWORD ulCommandLen,	OUT BYTE *pbOutData,	IN OUT DWORD *pulOutDataLen );

#endif
