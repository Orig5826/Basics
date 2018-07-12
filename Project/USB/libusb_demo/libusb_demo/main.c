
#include <stdio.h>
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



static uint16_t vendor_id;
static uint16_t product_id;
int main(void)
{
	int i = 0, r;
	libusb_device_handle * handle;
	//libusb_device * dev;
	uint8_t *report_buffer;
	char string[128];
	int size,num;
	uint8_t endpoint_in = 0, endpoint_out = 0;	// default IN and OUT endpoints

	//libusb模块初始化
	r = libusb_init(NULL);
	if (r < 0)
	{
		return r;
	}

	// 通过PID和VID来选择设备
	vendor_id = 0x4853;
	product_id = 0x084B;
	handle = libusb_open_device_with_vid_pid(NULL, vendor_id, product_id);
	if (handle == NULL) {
		printf("open VID=%04x,PID=%04x failed!\n", vendor_id, product_id);
		return -1;
	}

	// 这个暂不知道是用来做什么的
	// dev = libusb_get_device(handle);


	// 获取厂商信息，产品信息和序列号
	printf("\nReading string descriptors:\n");
	for (i = 1; i <= 3; i++) {
		if (libusb_get_string_descriptor_ascii(handle, i, (unsigned char*)string, sizeof(string)) > 0) {
			printf("   String (0x%02X): \"%s\"\n", i, string);
		}
	}


	// 对设备进行读写操作
	num = 0;
	size = 64;
	report_buffer = (uint8_t*)calloc(size, sizeof(uint8_t));
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
		endpoint_out = 0x02;
		//printf("\nTesting interrupt write using endpoint %02X...\n", endpoint_out);
		r = libusb_interrupt_transfer(handle, endpoint_out, report_buffer, size, &size, 5000);
		if (r >= 0) {
			//size = 64;	//调用完libusb_interrupt_transfer之后，size多了一个字节，为什么呢？
			//display_buffer_hex(report_buffer, size);
		}
		else {
			printf("   %s\n", libusb_strerror((enum libusb_error)r));
		}

		endpoint_in = 0x81;
		memset(report_buffer, 0x00, size);
		//printf("\nTesting interrupt read using endpoint %02X...\n", endpoint_in);
		r = libusb_interrupt_transfer(handle, endpoint_in, report_buffer, size, &size, 5000);
		if (r >= 0) {
			display_buffer_hex(report_buffer, size);
		}
		else {
			printf("   %s\n", libusb_strerror((enum libusb_error)r));
		}

		Sleep(1000);
#endif

		if (++ num >= 512)
		{
			break;
		}
	}

	free(report_buffer);
	libusb_exit(NULL);
	return 0;
}