
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include <hidsdi.h>
#include <cfgmgr32.h>

//
// These are the default device attributes set in the driver
// which are used to identify the device.
//
#define HIDMINI_DEFAULT_PID              0x084B
#define HIDMINI_DEFAULT_VID              0x4853

USAGE g_MyUsagePage = 0xFF00;
USAGE g_MyUsage = 0x01;

//
// STRING的最大可能长度
//
#define MAXIMUM_STRING_LENGTH			(128 * sizeof(WCHAR))
#define VHIDMINI_DEVICE_STRING_INDEX
//
// 获取厂家信息，产品信息，序列号
//
BOOLEAN
GetStrings(
	HANDLE File
)
{
	BOOLEAN bSuccess;
	BYTE* buffer;
	ULONG bufferLength;

	bufferLength = MAXIMUM_STRING_LENGTH;
	buffer = malloc(bufferLength);
	if (!buffer)
	{
		printf("malloc failed\n");
		return FALSE;
	}

	// 1.0 厂商信息
	ZeroMemory(buffer, bufferLength);
	bSuccess = HidD_GetManufacturerString(
		File,
		(PVOID)buffer,  //OUT PVOID  Buffer,
		bufferLength // IN ULONG  BufferLength
	);
	if (!bSuccess)
	{
		printf("Failed HidD_GetManufacturerString \n");
		goto exit;
	}
	else
	{
		printf("Manufacturer String: %S\n", (PWSTR)buffer);
	}

	// 2.0 产品信息
	ZeroMemory(buffer, bufferLength);
	bSuccess = HidD_GetProductString(
		File,
		(PVOID)buffer,  //OUT PVOID  Buffer,
		bufferLength	// IN ULONG  BufferLength
	);
	if (!bSuccess)
	{
		printf("Failed HidD_GetProductString \n");
		goto exit;
	}
	else
	{
		printf("Product String: %S\n", (PWSTR)buffer);
	}

	// 3.0 序列号
	ZeroMemory(buffer, bufferLength);
	bSuccess = HidD_GetSerialNumberString(
		File,
		(PVOID)buffer,  //OUT PVOID  Buffer,
		bufferLength // IN ULONG  BufferLength
	);

	if (!bSuccess)
	{
		printf("Failed HidD_GetSerialNumberString \n");
		goto exit;
	}
	else
	{
		printf("Serial Number String: %S\n", (PWSTR)buffer);
	}

exit:
	// 
	free(buffer);
	return bSuccess;
}


//
// 判断当前设备是否为指定的设备
//
BOOLEAN
CheckIfOurDevice(
	HANDLE file)
{
	HIDD_ATTRIBUTES attr; // Device attributes
	HIDP_CAPS		Caps; // The Capabilities of this hid device.
	PHIDP_PREPARSED_DATA Ppd; // The opaque parser info describing this device

	if (!HidD_GetAttributes(file, &attr))
	{
		printf("Error: HidD_GetAttributes failed \n");
		return FALSE;
	}

	printf("Device: [PID]%04X  [VID]%04X \n", attr.ProductID, attr.VendorID);
	if ((attr.VendorID != HIDMINI_DEFAULT_VID) || (attr.ProductID != HIDMINI_DEFAULT_PID))
	{
		//printf("Device attributes doesn't match the sample \n");
		return FALSE;
	}

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

	return FALSE;
}

//
// 在当前的设备中寻找指定的设备
//
BOOLEAN FindMatchDevice(LPGUID  InterfaceGuid, HANDLE * Handle)
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
	printf("Looking for our HID device (with UP = 0x%04X "
		"and Usage = 0x%04X)\n", g_MyUsagePage, g_MyUsage);

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

//
// 发送OUT包
//
BOOLEAN
WriteOutputData(
	_In_ HANDLE file,
	_In_ UCHAR * sBuf,
	_In_ ULONG sLen
)
{
	UCHAR * outputReport;
	ULONG outputReportSize ;
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
	outputReport[0] = 0x00;
	//
	// Wrute output data.
	//
	bSuccess = WriteFile(
		file,        // HANDLE hFile,
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
		printf("[OUT] ");
		for (ULONG i = 0; i < bytesWritten - 1; i++)
		{
			printf("%02x ", outputReport[i + 1]);
		}
		printf("\n");
	}

	free(outputReport);
	return (BOOLEAN)bSuccess;
}

//
// 接收IN包
//
BOOLEAN
ReadInputData(
	_In_ HANDLE file,
	_Out_ UCHAR * rBuf,
	_Out_ ULONG * rLen
)
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
	inBuf[0] = 0x00;
	//
	// get input data.
	//
	bSuccess = ReadFile(
		file,        // HANDLE hFile,
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
		printf("[In]:");
		for (ULONG i = 0; i < bytesRead - 1; i++)
		{
			printf("%02x ", inBuf[i + 1]);
		}
		printf("\n");
		
		memcpy(rBuf, inBuf + 1, bytesRead - 1);
		*rLen = bytesRead - 1;
	}

	free(inBuf);

	return (BOOLEAN)bSuccess;
}

INT __cdecl
main(
	_In_ ULONG argc,
	_In_reads_(argc) PCHAR argv[]
)
{
	GUID hidguid;
	HANDLE file = INVALID_HANDLE_VALUE;
	BOOLEAN found = FALSE;
	BOOLEAN bSuccess = FALSE;
	UCHAR sBuf[64];
	ULONG sLen = 64;
	UCHAR rBuf[64];
	ULONG rLen = 64;
	UCHAR temp = 0x00;;

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	//1.0 获取GUID
	HidD_GetHidGuid(&hidguid);

	found = FindMatchDevice(&hidguid, &file);
	if (found)
	{
		//
		// 1.0 获取HID设备信息
		//
		bSuccess = GetStrings(file);
		if (bSuccess == FALSE) {
			goto cleanup;
		}

		while (1)
		{
			//
			// 2.0 发送OUT包
			//
			sLen = 64;
			for (ULONG i = 0; i < sLen; i++)
			{
				sBuf[i] = (UCHAR)(temp + i);
			}
			temp++;
			bSuccess = WriteOutputData(file, sBuf, sLen);
			if (bSuccess == FALSE) {
				goto cleanup;
			}
			//
			// 3.0 接收IN包
			//
			rLen = 64;
			bSuccess = ReadInputData(file, rBuf, &rLen);
			if (bSuccess == FALSE) {
				goto cleanup;
			}

			printf("-------------------------------\n");
			Sleep(500);
		}
	}
	else
	{
		printf("** Failure ** Could not Find Our HID Device \n");
	}

cleanup:
	if (found && bSuccess == FALSE) {
		printf("** Failure ** One or More Commands To Device Failed !\n");
	}

	if (file != INVALID_HANDLE_VALUE) {
		CloseHandle(file);
	}

	system("pause");

	return (bSuccess ? 0 : 1);
}