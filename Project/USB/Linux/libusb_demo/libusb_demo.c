
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libusb.h"


// HID Class-Specific Requests values. See section 7.2 of the HID specifications
#define HID_GET_REPORT                0x01
#define HID_GET_IDLE                  0x02
#define HID_GET_PROTOCOL              0x03
#define HID_SET_REPORT                0x09
#define HID_SET_IDLE                  0x0A
#define HID_SET_PROTOCOL              0x0B
#define HID_REPORT_TYPE_INPUT         0x01
#define HID_REPORT_TYPE_OUTPUT        0x02
#define HID_REPORT_TYPE_FEATURE       0x03

static void display_buffer_hex(unsigned char *buffer, unsigned size)
{
	unsigned i, j, k;

	for (i = 0; i < size; i += 16) {
		printf("\n%08x  ", i);
		for (j = 0, k = 0; k < 16; j++, k++) {
			if (i + j < size) {
				printf("%02x", buffer[i + j]);
			}
			else {
				printf("  ");
			}
			printf(" ");
		}
		printf(" ");
		for (j = 0, k = 0; k < 16; j++, k++) {
			if (i + j < size) {
				if ((buffer[i + j] < 32) || (buffer[i + j] > 126)) {
					printf(".");
				}
				else {
					printf("%c", buffer[i + j]);
				}
			}
		}
	}
	printf("\n");
}


int usb_find(libusb_device_handle ** handle,uint16_t vendor_id,uint16_t product_id)
{
	libusb_device **devs;
	// 想了一下，暂时不使用该参数，试试
	// 这个参数主要用来做什么的？
	//libusb_context *ctx = NULL;

	int r = libusb_init(NULL);
	if (r < 0)
	{
		printf("Init Error\n");
		return -1;
	}

	int cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
	{
		printf("Get Device Error\n");
		return -1;
	}
	//libusb_device_handle * handle = NULL;

	for (int i = 0; i < cnt; i++)
	{
		struct libusb_device_descriptor desc;
		r = libusb_get_device_descriptor(devs[i], &desc);
		if (r < 0)
		{
			printf("Get Device Descriptor Error");
			return -1;
		}

		printf("Find.%02d : VID=%04x,PID=%04x\n",i + 1, desc.idVendor, desc.idProduct);
		if (desc.idVendor == vendor_id && desc.idProduct == product_id)
		{
			printf("Find the target device\n");
//* 两种设备的打开方式都可以
#if 0
			*handle = libusb_open_device_with_vid_pid(ctx, vendor_id, product_id);
			if (*handle == NULL)
#else
			r = libusb_open(devs[i], handle);
			if (r != 0)
#endif
			{
				printf("But open device(VID=%04x,PID=%04x) failed!\n",vendor_id,product_id);
				return -1;
			}

			return 0;
		}
	}
	printf("I don't find my device[VID=%04x,PID=%04x]\n",vendor_id,product_id);
	return -1;
}

int test_hid(void)
{
	int i = 0, r;
	libusb_device_handle * handle;
	//libusb_device * dev;
	uint8_t *report_buffer;
	char string[128];
	int size,num;
	uint8_t endpoint_in = 0, endpoint_out = 0;	// default IN and OUT endpoints
	static uint16_t vendor_id;
	static uint16_t product_id;


//#  通过PID和VID来选择设备
#if 0
	// 我的hsc32k1 例程
	vendor_id = 0x4853;
	product_id = 0x084B;
	endpoint_out = 0x02;
	endpoint_in = 0x81;
#else
	// 我的stm32 例程
	vendor_id = 0x0483;
	product_id = 0x5750;
	endpoint_out = 0x01;
	endpoint_in = 0x81;
#endif


//* usb_find函数是单独封装用来寻找指定设备的
#if 0
	//libusb模块初始化
	r = libusb_init(NULL);
	if (r < 0)
	{
		return r;
	}
	handle = libusb_open_device_with_vid_pid(NULL, vendor_id, product_id);
	if (handle == NULL) {
		printf("open VID=%04x,PID=%04x failed!\n", vendor_id, product_id);
		return -1;
	}
#else
	r = usb_find(&handle, vendor_id, product_id);
	if (r < 0)
	{
		return r;
	}
#endif
	// 获取厂商信息，产品信息和序列号
	printf("\nReading string descriptors:\n");
	for (i = 1; i <= 3; i++) {
		if (libusb_get_string_descriptor_ascii(handle, i, (unsigned char*)string, sizeof(string)) > 0) {
			printf("   String (0x%02X): \"%s\"\n", i, string);
		}
	}

	// Linux 下必须添加，否则通过端点收发数据会失败
	r = libusb_set_auto_detach_kernel_driver(handle, 1);
	if (r != LIBUSB_SUCCESS) {
		printf("set_auto_detach_kernel_driver    Failed.\n");
	}
	printf("\nClaiming interface %d...\n", 0);
	r = libusb_claim_interface(handle, 0);
	if (r != LIBUSB_SUCCESS) {
		printf("claim interface Failed.\n");
	}

	// 对设备进行读写操作
	num = 0;
	size = 64;
	report_buffer = (uint8_t*)calloc(size, sizeof(uint8_t));
	if(report_buffer == NULL)
	{
		printf("calloc memory Error!\n");
	}
	while (1)
	{
		for (i = 0; i < size; i++)
		{
			report_buffer[i] = (num + i) & 0xff;
		}
#if 0
		r = libusb_control_transfer(handle, LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE,
			HID_SET_REPORT, (HID_REPORT_TYPE_OUTPUT << 8) | 0x00, 0, report_buffer, (uint16_t)size, 5000);
		if (r >= 0) {
			//display_buffer_hex(report_buffer, size);
		}
		else
		{
			switch (r) {
			case LIBUSB_ERROR_TIMEOUT:
				printf("   Timeout! Please make sure you act on the device within the 5 seconds allocated...\n");
				break;
			case LIBUSB_ERROR_PIPE:
				printf("   Detected stall - resetting pipe...\n");
				libusb_clear_halt(handle, 0);
				break;
			default:
				printf("   Error: %s\n", libusb_strerror((enum libusb_error)r));
				break;
			}
		}

		memset(report_buffer, 0x00, size);
		r = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE,
			HID_GET_REPORT, (HID_REPORT_TYPE_INPUT << 8) | 0x00, 0, report_buffer, (uint16_t)size, 5000);
		if (r >= 0) {
			display_buffer_hex(report_buffer, size);
		}
		else
		{
			switch (r) {
			case LIBUSB_ERROR_TIMEOUT:
				printf("   Timeout! Please make sure you act on the device within the 5 seconds allocated...\n");
				break;
			case LIBUSB_ERROR_PIPE:
				printf("   Detected stall - resetting pipe...\n");
				libusb_clear_halt(handle, 0);
				break;
			default:
				printf("   Error: %s\n", libusb_strerror((enum libusb_error)r));
				break;
			}
		}

		//Sleep(1000);
#else
		//printf("\nTesting interrupt write using endpoint %02X...\n", endpoint_out);
		r = libusb_interrupt_transfer(handle, endpoint_out, report_buffer, size, &size, 1000);
		if (r >= 0) {
			//size = 64;	//调用完libusb_interrupt_transfer之后，size多了一个字节，为什么呢？
			//display_buffer_hex(report_buffer, size);
		}
		else {
			printf("   %s\n", libusb_strerror((enum libusb_error)r));
		}

		memset(report_buffer, 0x00, size);
		//printf("\nTesting interrupt read using endpoint %02X...\n", endpoint_in);
		r = libusb_interrupt_transfer(handle, endpoint_in, report_buffer, size, &size, 1000);
		if (r >= 0) {
			display_buffer_hex(report_buffer, size);
		}
		else {
			printf("   %s\n", libusb_strerror((enum libusb_error)r));
		}

		sleep(1);
#endif

		if (++ num >= 5)
		{
			break;
		}
	}

	free(report_buffer);
	libusb_close(handle);
	libusb_exit(NULL);
	printf("libusb_exit!\n");
	return 0;
}

// Section 5.1: Command Block Wrapper (CBW)
struct command_block_wrapper {
	uint8_t dCBWSignature[4];
	uint32_t dCBWTag;
	uint32_t dCBWDataTransferLength;
	uint8_t bmCBWFlags;
	uint8_t bCBWLUN;
	uint8_t bCBWCBLength;
	uint8_t CBWCB[16];
};
// Section 5.2: Command Status Wrapper (CSW)
struct command_status_wrapper {
	uint8_t dCSWSignature[4];
	uint32_t dCSWTag;
	uint32_t dCSWDataResidue;
	uint8_t bCSWStatus;
};

static int send_mass_storage_command(libusb_device_handle *handle, uint8_t endpoint, uint8_t direction,int data_length, uint32_t *ret_tag)
{
	static uint32_t tag = 1;
	int i, r, size;
	struct command_block_wrapper cbw;

	if (endpoint & LIBUSB_ENDPOINT_IN) {
		printf("send_mass_storage_command: cannot send command on IN endpoint\n");
		return -1;
	}

	memset(&cbw, 0, sizeof(cbw));
	cbw.dCBWSignature[0] = 'U';
	cbw.dCBWSignature[1] = 'S';
	cbw.dCBWSignature[2] = 'B';
	cbw.dCBWSignature[3] = 'C';

	*ret_tag = tag;
	cbw.dCBWTag = tag++;

	cbw.dCBWDataTransferLength = data_length;
	cbw.bmCBWFlags = direction;
	cbw.bCBWLUN = 0x00;
	cbw.bCBWCBLength = 0x01;

	// 自定义命令
	cbw.CBWCB[0] = 0xff;

	i = 0;
	do {
		// The transfer length must always be exactly 31 bytes.
		r = libusb_bulk_transfer(handle, endpoint, (unsigned char*)&cbw, 31, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(handle, endpoint);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i < 3));
	if (r != LIBUSB_SUCCESS) {
		printf("   send_mass_storage_command: %s\n", libusb_strerror((enum libusb_error)r));
		return -1;
	}
	return 0;
}

static int get_mass_storage_status(libusb_device_handle *handle, uint8_t endpoint, uint32_t expected_tag)
{
	int i, r, size;
	struct command_status_wrapper csw;

	// The device is allowed to STALL this transfer. If it does, you have to
	// clear the stall and try again.
	i = 0;
	do {
		r = libusb_bulk_transfer(handle, endpoint, (unsigned char*)&csw, 13, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(handle, endpoint);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<3));

	if (r != LIBUSB_SUCCESS) {
		printf("   get_mass_storage_status: %s\n", libusb_strerror((enum libusb_error)r));
		return -1;
	}
	if (size != 13) {
		printf("   get_mass_storage_status: received %d bytes (expected 13)\n", size);
		return -1;
	}
	
	if (csw.dCSWTag != expected_tag) {
		printf("   get_mass_storage_status: mismatched tags (expected %08X, received %08X)\n",
			expected_tag, csw.dCSWTag);
		return -1;
	}

	//printf("   Mass Storage Status: %02X (%s)\n", csw.bCSWStatus, csw.bCSWStatus?"FAILED":"Success");
	if (csw.bCSWStatus) {
		printf("   Mass Storage Status: %02X (%s)\n", csw.bCSWStatus, csw.bCSWStatus?"FAILED":"Success");
		// REQUEST SENSE is appropriate only if bCSWStatus is 1, meaning that the
		// command failed somehow.  Larger values (2 in particular) mean that
		// the command couldn't be understood.
		if (csw.bCSWStatus == 1)
			return -2;	// request Get Sense
		else
			return -1;
	}

	// In theory we also should check dCSWDataResidue.  But lots of devices
	// set it wrongly.
	return 0;
}

// 该函数内容因某些原因并没有调试通过
// 暂时保留，不再修改
// 2018.7.13
int test_scsi(void)
{
	libusb_device_handle * handle;
	// default IN and OUT endpoints
	uint8_t endpoint_in = 0, endpoint_out = 0;
	char string[128];
	//uint8_t *report_buffer;
	//int size, num;
	int i = 0, r;
	static uint16_t vendor_id;
	static uint16_t product_id;

	// libusb模块初始化
	// 现在发现的问题
	// 工程中的示例代码枚举成MSD设备，但是
	// 使用libusb不能正常通过PID和VID打开
	// 这是为什么
	// -----------------------------------------
	// 经过百度查询资料
	// libusb在windows下仅仅支持用户态
	// 因此仅仅支持HID设备，其他诸如scsi设备不行
	// --- 确定是这个问题吗？
	vendor_id = 0x2309;
	product_id = 0x0606;
#if 0
	vendor_id = 0x0483;
	product_id = 0x5750;
#endif
	r = usb_find(&handle,vendor_id, product_id);
	if (r < 0)
	{
		return -1;
	}

#if 0
	// SCSI 设备或者信息失败？为什么
	// 获取厂商信息，产品信息和序列号
	printf("\nReading string descriptors:\n");
	for (i = 1; i <= 3; i++) {
		if (libusb_get_string_descriptor_ascii(handle, i, (unsigned char*)string, sizeof(string)) > 0) {
			printf("   String (0x%02X): \"%s\"\n", i, string);
		}
	}
#endif
	r = libusb_set_auto_detach_kernel_driver(handle, 1);
	if (r != LIBUSB_SUCCESS) {
		printf("set_auto_detach_kernel_driver    Failed.\n");
	}
	printf("\nClaiming interface %d...\n", 0);
	r = libusb_claim_interface(handle, 0);
	if (r != LIBUSB_SUCCESS) {
		printf("   Failed.\n");
		switch (r)
		{
		case LIBUSB_ERROR_NOT_FOUND:
			printf("the requested interface does not exist\n");
			break;
		case LIBUSB_ERROR_BUSY:
			printf("another program or driver has claimed the interface\n");
			break;
		case LIBUSB_ERROR_NO_DEVICE:
			printf("the device has been disconnected\n");
			break;
		default:
			printf("code on other failure");
			break;
		}
	}

	// 自定义设备
	endpoint_in = 0x81;	// 最高bit为1，DeviceToHost
	endpoint_out = 0x02;
	{
		uint32_t tag;
		uint32_t size;
		uint8_t sBuf[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
		uint8_t cbw[31] = {0x55, 0x53, 0x42, 0x43, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff,
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		uint8_t rBuf[8];
		uint8_t csw[13];
		
		// 发送
		send_mass_storage_command(handle,endpoint_out,0x00,8,&tag);
		if(0 != libusb_bulk_transfer(handle,endpoint_out,sBuf,8,&size,0))
		{
			printf("Write 失败！\n");
			goto end;
		}
		get_mass_storage_status(handle,endpoint_in,tag);
		display_buffer_hex(sBuf,size);

		// 接收
		send_mass_storage_command(handle,endpoint_out,0x80,8,&tag);
		if(0 != libusb_bulk_transfer(handle,endpoint_in,rBuf,8,&size,0))
		{
			printf("Read 失败！\n");
			goto end;
		}
		get_mass_storage_status(handle,endpoint_in,tag);
		display_buffer_hex(rBuf,size);
#if 0
		if(0 != libusb_bulk_transfer(handle,endpoint_out,cbw,31,&size,0))
		{
			printf("CBW 发送失败！\n");
			goto end;
		}
		if(0 != libusb_bulk_transfer(handle,endpoint_out,sBuf,8,&size,0))
		{
			printf("Write 失败！\n");
			goto end;
		}
		display_buffer_hex(sBuf,0x08);
		if(0 != libusb_bulk_transfer(handle,endpoint_in,csw,13,&size,0))
		{
			printf("CSW 接收失败！\n");
			goto end;
		}

		cbw[12] |= 0x80; 
		if(0 != libusb_bulk_transfer(handle,endpoint_out,cbw,31,&size,0))
		{
			printf("CBW 发送失败！\n");
			goto end;
		}
		if(0 != libusb_bulk_transfer(handle,endpoint_in,rBuf,8,&size,0))
		{
			printf("Read 失败！\n");
			goto end;
		}
		display_buffer_hex(rBuf,0x08);
		if(0 != libusb_bulk_transfer(handle,endpoint_in,csw,13,&size,0))
		{
			printf("CSW 接收失败！\n");
			goto end;
		}
#endif
	}
end:
	libusb_release_interface(handle,0);
	//free(report_buffer);
	libusb_close(handle);
	libusb_exit(NULL);
	printf("libusb_exit!\n");
	return 0;
}


int main(int argc,char * argv[])
{
	if (argc == 1)
	{
		return test_hid();
	}
	else
	{
		if (argc != 2)
		{
			return -1;
		}
		if (0 == strcmp(argv[1],"0"))
		{
			return test_hid();
		}
		else if (0 == strcmp(argv[1], "1"))
		{
			return test_scsi();
		}
	}

	return 0;
}