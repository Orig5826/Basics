
#include "usb_drive.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <hidsdi.h>
#include <cfgmgr32.h>


//#define USB_DRIVER_DEBUG


//
// These are the default device attributes set in the driver
// which are used to identify the device.
//
#define HIDMINI_DEFAULT_PID              0x084B
#define HIDMINI_DEFAULT_VID              0x4853

static USHORT s_hid_device_pid;
static USHORT s_hid_device_vid;
//
// STRING的最大可能长度
//
#define MAXIMUM_STRING_LENGTH			(128 * sizeof(WCHAR))
//
// 全局句柄
//
static HANDLE s_hUsb_Hid_Device;
//
//  函数声明
//
static BOOLEAN FindMatchDevice(LPGUID  InterfaceGuid, HANDLE * Handle);


/*
 * 连接 
 */
BOOL USB_HID_Connect(HID_Config * hid_cfg)
{
	GUID hidguid;
	BOOLEAN bSuccess = FALSE;

	if (hid_cfg != NULL)
	{
		// 用来连接指定设备
		s_hid_device_pid = hid_cfg->PID;
		s_hid_device_vid = hid_cfg->VID;
	}
	else
	{
		s_hid_device_pid = HIDMINI_DEFAULT_PID;
		s_hid_device_vid = HIDMINI_DEFAULT_VID;
	}

	// 连接指定设备
	HidD_GetHidGuid(&hidguid);
	bSuccess = FindMatchDevice(&hidguid, &s_hUsb_Hid_Device);
	if (bSuccess != TRUE)
	{
		printf(" --> I don't find my device!\n");
	}

	return bSuccess;
}

/*
* 关闭
*/
void USB_HID_Close(void)
{
	if (s_hUsb_Hid_Device != INVALID_HANDLE_VALUE) {
		CloseHandle(s_hUsb_Hid_Device);
	}
}

/*
* 写入数据
*/
BOOLEAN USB_HID_Write(unsigned char ReportID,unsigned char * sBuf, unsigned int sLen)
{
	UCHAR * outputReport;
	ULONG outputReportSize;
	BOOL bSuccess;
	DWORD bytesWritten;

	outputReportSize = sLen + 1;
	outputReport = (UCHAR *)malloc(outputReportSize);
	if (!outputReport)
	{
		printf("malloc failed\n");
		return FALSE;
	}

	memcpy(outputReport + 1, sBuf, sLen);
	outputReport[0] = ReportID;
	//
	// Wrute output data.
	//
	bSuccess = WriteFile(
		s_hUsb_Hid_Device,        // HANDLE hFile,
		(PVOID)outputReport,      // LPVOID lpBuffer,
		outputReportSize, // DWORD nNumberOfBytesToRead,
		&bytesWritten,    // LPDWORD lpNumberOfBytesRead,
		NULL         // LPOVERLAPPED lpOverlapped
	);

	if (!bSuccess)
	{
		printf("failed WriteFile \n");
	}
	else
	{
#ifdef USB_DRIVER_DEBUG
		printf("[OUT] ");
		for (ULONG i = 0; i < bytesWritten - 1; i++)
		{
			printf("%02x ", outputReport[i + 1]);
		}
		printf("\n");
#endif
	}

	free(outputReport);
	return (BOOLEAN)bSuccess;
}

/*
* 读取数据
*/
BOOLEAN USB_HID_Read(unsigned char ReportID,unsigned char * rBuf, unsigned int * rLen)
{
	ULONG bufferSize;
	UCHAR * inBuf;
	BOOL bSuccess;
	DWORD bytesRead;

	bufferSize = *rLen + 1;
	inBuf = (UCHAR *)malloc(bufferSize);
	if (!inBuf)
	{
		printf("malloc failed\n");
		return FALSE;
	}

	ZeroMemory(inBuf, bufferSize);
	inBuf[0] = ReportID;
	//
	// get input data.
	//
	bSuccess = ReadFile(
		s_hUsb_Hid_Device,	// HANDLE hFile,
		inBuf,      // LPVOID lpBuffer,
		bufferSize,  // DWORD nNumberOfBytesToRead,
		&bytesRead,  // LPDWORD lpNumberOfBytesRead,
		NULL         // LPOVERLAPPED lpOverlapped
	);

	if (!bSuccess)
	{
		printf("failed ReadFile \n");
	}
	else
	{
#ifdef USB_DRIVER_DEBUG
		printf("[In]: \n");
		for (ULONG i = 0; i < bytesRead - 1; i++)
		{
			printf("%02x ", inBuf[i + 1]);
		}
		printf("\n");
#endif
		memcpy(rBuf, inBuf + 1, bytesRead - 1);
		*rLen = bytesRead - 1;
	}

	free(inBuf);

	return (BOOLEAN)bSuccess;
}

/*
* 获取厂家，产品，序列号等信息
* @param rLen 表示rBuf的最大长度
*/
BOOLEAN USB_HID_GetString(unsigned char * rBuf, unsigned int rLen, unsigned char infotype)
{
	BOOLEAN bSuccess = FALSE;;

	ZeroMemory(rBuf,rLen);
	switch(infotype)
	{
		case GET_MANUFACTURE:
		{
			// 1.0 厂商信息
			bSuccess = HidD_GetManufacturerString(
				s_hUsb_Hid_Device,
				(PVOID)rBuf,
				rLen
			);
			if (!bSuccess)
			{
				unsigned int i = 0;
				char * p = "Get_ManufactureString Failed!";
				for (i = 0; i < strlen(p); i++)
				{
					rBuf[i] = *(p + i);
				}
				rBuf[i] = '\0';
			}
		}break;
		case GET_PRODUCT:
		{
			// 2.0 产品信息
			bSuccess = HidD_GetProductString(
				s_hUsb_Hid_Device,
				(PVOID)rBuf,  //OUT PVOID  Buffer,
				rLen	// IN ULONG  BufferLength
			);
			if (!bSuccess)
			{
				unsigned int i = 0;
				char * p = "Get_ProductString Failed!";
				for (i = 0; i < strlen(p); i++)
				{
					rBuf[i] = *(p + i);
				}
				rBuf[i] = '\0';
			}
		}break;
		case GET_SERIALNUM:
		{
			// 3.0 序列号
			bSuccess = HidD_GetSerialNumberString(
				s_hUsb_Hid_Device,
				(PVOID)rBuf,
				rLen
			);

			if (!bSuccess)
			{
				unsigned int i = 0;
				char * p = "Get_SerialNumber Failed!";
				for (i = 0; i < strlen(p); i++)
				{
					rBuf[i] = *(p + i);
				}
				rBuf[i] = '\0';
			}
		}break;
		default:
			break;
	}

	return bSuccess;
}

//
// 判断当前设备是否为指定的设备
//
static BOOLEAN
CheckIfOurDevice(
	HANDLE file)
{
	HIDD_ATTRIBUTES attr; // Device attributes

	if (!HidD_GetAttributes(file, &attr))
	{
		printf("Error: HidD_GetAttributes failed \n");
		return FALSE;
	}

	printf("Device: [PID]%04X  [VID]%04X \n", attr.ProductID, attr.VendorID);
	// 用PID和VID来查找设备
	if ((attr.VendorID == s_hid_device_vid) && (attr.ProductID == s_hid_device_pid))
	{
		printf(" --> I've found my Device\n");
		return TRUE;
	}

#if 0
	HIDP_CAPS		Caps; // The Capabilities of this hid device.
	PHIDP_PREPARSED_DATA Ppd; // The opaque parser info describing this device

	// 用来获取HID报告描述符长度等信息
	// 在此处是为了结合后面的程序进行设备过滤
	// 因目前仅仅想通过PID和VID过滤，因此去除
	if (!HidD_GetPreparsedData(file, &Ppd))
	{
		printf("Error: HidD_GetPreparsedData failed \n");
		return FALSE;
	}

	if (!HidP_GetCaps(Ppd, &Caps))
	{
		printf("Error: HidP_GetCaps failed \n");
		HidD_FreePreparsedData(Ppd);
		return FALSE;
	}

	if ((Caps.UsagePage == g_MyUsagePage) && (Caps.Usage == g_MyUsage)) {
		printf("[Success] This Is My Device\n");
		return TRUE;
	}
#endif

	return FALSE;
}
//
// 在当前的设备中寻找指定的设备
//
static BOOLEAN FindMatchDevice(LPGUID  InterfaceGuid, HANDLE * Handle)
{
	CONFIGRET cr = CR_SUCCESS;
	ULONG deviceInterfaceListLength = 0;
	PWSTR deviceInterfaceList = NULL;
	PWSTR currentInterface;
	HANDLE devHandle = INVALID_HANDLE_VALUE;
	BOOLEAN bRet = FALSE;

	if (NULL == Handle) {
		printf("Error: Invalid device handle parameter\n");
		return FALSE;
	}
	*Handle = INVALID_HANDLE_VALUE;

	//
	// 1.0 寻找当前存在的设备总数
	//
	cr = CM_Get_Device_Interface_List_Size(
		&deviceInterfaceListLength,
		InterfaceGuid,
		NULL,
		CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
	if (cr != CR_SUCCESS) {
		printf("Error 0x%x retrieving device interface list size.\n", cr);
		goto clean0;
	}
	if (deviceInterfaceListLength <= 1) {
		bRet = FALSE;
		printf("Error: No active device interfaces found.\n"
			" Is the sample driver loaded?");
		goto clean0;
	}

	// 
	// 2.0 寻找当前存在的设备
	//
	deviceInterfaceList = (PWSTR)malloc(deviceInterfaceListLength * sizeof(WCHAR));
	if (deviceInterfaceList == NULL) {
		printf("Error allocating memory for device interface list.\n");
		goto clean0;
	}
	ZeroMemory(deviceInterfaceList, deviceInterfaceListLength * sizeof(WCHAR));
	cr = CM_Get_Device_Interface_List(
		InterfaceGuid,
		NULL,
		deviceInterfaceList,
		deviceInterfaceListLength,
		CM_GET_DEVICE_INTERFACE_LIST_PRESENT
	);

	//
	// 3. 枚举该接口类的设备
	//
	for (currentInterface = deviceInterfaceList;
		*currentInterface;
		currentInterface += wcslen(currentInterface) + 1) {

		devHandle = CreateFile(currentInterface,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		if (INVALID_HANDLE_VALUE == devHandle) {
			//printf("Warning: CreateFile failed: %d\n", GetLastError());
			continue;
		}

		if (CheckIfOurDevice(devHandle)) {
			bRet = TRUE;
			*Handle = devHandle;
		}
		else {
			CloseHandle(devHandle);
		}
	}

clean0:
	if (deviceInterfaceList != NULL) {
		free(deviceInterfaceList);
	}
	if (CR_SUCCESS != cr) {
		bRet = FALSE;
	}

	printf("\n");
	return bRet;
}

void usb_hid_test(void)
{
	//printf("usb_hid_test\n");
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = i;
	}
	printf("usb_hid_test!\n");
}
