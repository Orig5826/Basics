
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
		printf("\n  %08x  ", i);
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
	// ����һ�£���ʱ��ʹ�øò���������
	// ���������Ҫ������ʲô�ģ�
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
//* �����豸�Ĵ򿪷�ʽ������
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


//#  ͨ��PID��VID��ѡ���豸
#if 0
	// �ҵ�hsc32k1 ����
	vendor_id = 0x4853;
	product_id = 0x084B;
	endpoint_out = 0x02;
	endpoint_in = 0x81;
#else
	// �ҵ�stm32 ����
	vendor_id = 0x0483;
	product_id = 0x5750;
	endpoint_out = 0x01;
	endpoint_in = 0x81;
#endif


//* usb_find�����ǵ�����װ����Ѱ��ָ���豸��
#if 0
	//libusbģ���ʼ��
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
	// ��ȡ������Ϣ����Ʒ��Ϣ�����к�
	printf("\nReading string descriptors:\n");
	for (i = 1; i <= 3; i++) {
		if (libusb_get_string_descriptor_ascii(handle, i, (unsigned char*)string, sizeof(string)) > 0) {
			printf("   String (0x%02X): \"%s\"\n", i, string);
		}
	}

	// Linux �±�����ӣ�����ͨ���˵��շ����ݻ�ʧ��
	r = libusb_set_auto_detach_kernel_driver(handle, 1);
	if (r != LIBUSB_SUCCESS) {
		printf("set_auto_detach_kernel_driver    Failed.\n");
	}
	printf("\nClaiming interface %d...\n", 0);
	r = libusb_claim_interface(handle, 0);
	if (r != LIBUSB_SUCCESS) {
		printf("claim interface Failed.\n");
	}

	// ���豸���ж�д����
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
			//size = 64;	//������libusb_interrupt_transfer֮��size����һ���ֽڣ�Ϊʲô�أ�
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

// �ú���������ĳЩԭ��û�е���ͨ��
// ��ʱ�����������޸�
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

	// libusbģ���ʼ��
	// ���ڷ��ֵ�����
	// �����е�ʾ������ö�ٳ�MSD�豸������
	// ʹ��libusb��������ͨ��PID��VID��
	// ����Ϊʲô
	// -----------------------------------------
	// �����ٶȲ�ѯ����
	// libusb��windows�½���֧���û�̬
	// ��˽���֧��HID�豸����������scsi�豸����
	// --- ȷ�������������
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

#if 1
	// SCSI �豸������Ϣʧ�ܣ�Ϊʲô
	// ��ȡ������Ϣ����Ʒ��Ϣ�����к�
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