
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



#define ERR_EXIT(errcode) do { printf("   %s\n", libusb_strerror((enum libusb_error)errcode)); return -1; } while (0)
#define CALL_CHECK(fcall) do { int _r=fcall; if (_r < 0) ERR_EXIT(_r); } while (0)
#define CALL_CHECK_CLOSE(fcall, hdl) do { int _r=fcall; if (_r < 0) { libusb_close(hdl); ERR_EXIT(_r); } } while (0)
#define B(x) (((x)!=0)?1:0)
#define be_to_int32(buf) (((buf)[0]<<24)|((buf)[1]<<16)|((buf)[2]<<8)|(buf)[3])
// MSD 
#define RETRY_MAX                     5
#define REQUEST_SENSE_LENGTH          0x12
#define INQUIRY_LENGTH                0x24
#define READ_CAPACITY_LENGTH          0x08
// Mass Storage Requests values. See section 3 of the Bulk-Only Mass Storage Class specifications
#define BOMS_RESET                    0xFF
#define BOMS_GET_MAX_LUN              0xFE


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
static const uint8_t cdb_length[256] = {
//	 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	06,06,06,06,06,06,06,06,06,06,06,06,06,06,06,06,  //  0
	06,06,06,06,06,06,06,06,06,06,06,06,06,06,06,06,  //  1
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,  //  2
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,  //  3
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,  //  4
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,  //  5
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,  //  6
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,  //  7
	16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,  //  8
	16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,  //  9
	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,  //  A
	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,  //  B
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,  //  C
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,  //  D
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,  //  E
	00,00,00,00,00,00,00,00,00,00,00,00,00,06,06,06,  //  F
};

static int send_mass_storage_command(libusb_device_handle *handle, uint8_t endpoint, uint8_t lun,
	uint8_t *cdb, uint8_t direction, int data_length, uint32_t *ret_tag)
{
	static uint32_t tag = 1;
	uint8_t cdb_len;
	int i, r, size;
	struct command_block_wrapper cbw;

	if (cdb == NULL) {
		return -1;
	}

	if (endpoint & LIBUSB_ENDPOINT_IN) {
		printf("send_mass_storage_command: cannot send command on IN endpoint\n");
		return -1;
	}

	cdb_len = cdb_length[cdb[0]];
	if ((cdb_len == 0) || (cdb_len > sizeof(cbw.CBWCB))) {
		printf("send_mass_storage_command: don't know how to handle this command (%02X, length %d)\n",
			cdb[0], cdb_len);
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
	cbw.bCBWLUN = lun;
	// Subclass is 1 or 6 => cdb_len
	cbw.bCBWCBLength = cdb_len;
	memcpy(cbw.CBWCB, cdb, cdb_len);

	i = 0;
	do {
		// The transfer length must always be exactly 31 bytes.
		r = libusb_bulk_transfer(handle, endpoint, (unsigned char*)&cbw, 31, &size, 1000);
		if (r == LIBUSB_ERROR_PIPE) {
			libusb_clear_halt(handle, endpoint);
		}
		i++;
	} while ((r == LIBUSB_ERROR_PIPE) && (i<RETRY_MAX));
	if (r != LIBUSB_SUCCESS) {
		printf("   send_mass_storage_command: %s\n", libusb_strerror((enum libusb_error)r));
		return -1;
	}

	printf("   sent %d CDB bytes\n", cdb_len);
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
	} while ((r == LIBUSB_ERROR_PIPE) && (i<RETRY_MAX));

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
	// For this test, we ignore the dCSWSignature check for validity...
	printf("   Mass Storage Status: %02X (%s)\n", csw.bCSWStatus, csw.bCSWStatus?"FAILED":"Success");
	if (csw.dCSWTag != expected_tag)
		return -1;
	if (csw.bCSWStatus) {
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
static void get_sense(libusb_device_handle *handle, uint8_t endpoint_in, uint8_t endpoint_out)
{
	uint8_t cdb[16];	// SCSI Command Descriptor Block
	uint8_t sense[18];
	uint32_t expected_tag;
	int size;
	int rc;

	// Request Sense
	printf("Request Sense:\n");
	memset(sense, 0, sizeof(sense));
	memset(cdb, 0, sizeof(cdb));
	cdb[0] = 0x03;	// Request Sense
	cdb[4] = REQUEST_SENSE_LENGTH;

	send_mass_storage_command(handle, endpoint_out, 0, cdb, LIBUSB_ENDPOINT_IN, REQUEST_SENSE_LENGTH, &expected_tag);
	rc = libusb_bulk_transfer(handle, endpoint_in, (unsigned char*)&sense, REQUEST_SENSE_LENGTH, &size, 1000);
	if (rc < 0)
	{
		printf("libusb_bulk_transfer failed: %s\n", libusb_error_name(rc));
		return;
	}
	printf("   received %d bytes\n", size);

	if ((sense[0] != 0x70) && (sense[0] != 0x71)) {
		printf("   ERROR No sense data\n");
	} else {
		printf("   ERROR Sense: %02X %02X %02X\n", sense[2]&0x0F, sense[12], sense[13]);
	}
	// Strictly speaking, the get_mass_storage_status() call should come
	// before these printf() lines.  If the status is nonzero then we must
	// assume there's no data in the buffer.  For xusb it doesn't matter.
	get_mass_storage_status(handle, endpoint_in, expected_tag);
}

// Mass Storage device to test bulk transfers (non destructive test)
static int test_mass_storage(libusb_device_handle *handle, uint8_t endpoint_in, uint8_t endpoint_out)
{
	int r, size;
	uint8_t lun;
	uint32_t expected_tag;
	uint32_t i, max_lba, block_size;
	double device_size;
	uint8_t cdb[16];	// SCSI Command Descriptor Block
	uint8_t buffer[64];
	char vid[9], pid[9], rev[5];
	unsigned char *data;
	FILE *fd;

	printf("Reading Max LUN:\n");
	r = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE,
		BOMS_GET_MAX_LUN, 0, 0, &lun, 1, 1000);
	// Some devices send a STALL instead of the actual value.
	// In such cases we should set lun to 0.
	if (r == 0) {
		lun = 0;
	} else if (r < 0) {
		printf("   Failed: %s", libusb_strerror((enum libusb_error)r));
	}
	printf("   Max LUN = %d\n", lun);

	// Send Inquiry
	printf("Sending Inquiry:\n");
	memset(buffer, 0, sizeof(buffer));
	memset(cdb, 0, sizeof(cdb));
	cdb[0] = 0x12;	// Inquiry
	cdb[4] = INQUIRY_LENGTH;

	send_mass_storage_command(handle, endpoint_out, lun, cdb, LIBUSB_ENDPOINT_IN, INQUIRY_LENGTH, &expected_tag);
	CALL_CHECK(libusb_bulk_transfer(handle, endpoint_in, (unsigned char*)&buffer, INQUIRY_LENGTH, &size, 1000));
	printf("   received %d bytes\n", size);
	// The following strings are not zero terminated
	for (i=0; i<8; i++) {
		vid[i] = buffer[8+i];
		pid[i] = buffer[16+i];
		rev[i/2] = buffer[32+i/2];	// instead of another loop
	}
	vid[8] = 0;
	pid[8] = 0;
	rev[4] = 0;
	printf("   VID:PID:REV \"%8s\":\"%8s\":\"%4s\"\n", vid, pid, rev);
	if (get_mass_storage_status(handle, endpoint_in, expected_tag) == -2) {
		get_sense(handle, endpoint_in, endpoint_out);
	}

	// Read capacity
	printf("Reading Capacity:\n");
	memset(buffer, 0, sizeof(buffer));
	memset(cdb, 0, sizeof(cdb));
	cdb[0] = 0x25;	// Read Capacity

	send_mass_storage_command(handle, endpoint_out, lun, cdb, LIBUSB_ENDPOINT_IN, READ_CAPACITY_LENGTH, &expected_tag);
	CALL_CHECK(libusb_bulk_transfer(handle, endpoint_in, (unsigned char*)&buffer, READ_CAPACITY_LENGTH, &size, 1000));
	printf("   received %d bytes\n", size);
	max_lba = be_to_int32(&buffer[0]);
	block_size = be_to_int32(&buffer[4]);
	device_size = ((double)(max_lba+1))*block_size/(1024*1024*1024);
	printf("   Max LBA: %08X, Block Size: %08X (%.2f GB)\n", max_lba, block_size, device_size);
	if (get_mass_storage_status(handle, endpoint_in, expected_tag) == -2) {
		get_sense(handle, endpoint_in, endpoint_out);
	}

#if 0
	// coverity[tainted_data]
	data = (unsigned char*) calloc(1, block_size);
	if (data == NULL) {
		printf("   unable to allocate data buffer\n");
		return -1;
	}

	// Send Read
	printf("Attempting to read %u bytes:\n", block_size);
	memset(cdb, 0, sizeof(cdb));

	cdb[0] = 0x28;	// Read(10)
	cdb[8] = 0x01;	// 1 block

	send_mass_storage_command(handle, endpoint_out, lun, cdb, LIBUSB_ENDPOINT_IN, block_size, &expected_tag);
	libusb_bulk_transfer(handle, endpoint_in, data, block_size, &size, 5000);
	printf("   READ: received %d bytes\n", size);
	if (get_mass_storage_status(handle, endpoint_in, expected_tag) == -2) {
		get_sense(handle, endpoint_in, endpoint_out);
	} else {
		display_buffer_hex(data, size);
	}
	free(data);
#endif

	// SCSI_DEMO : GET CHALLENGE
	printf("Get challenge %u bytes:\n", 10);
	memset(cdb, 0, sizeof(cdb));
	cdb[0] = 0xfe;	// UserCommond
	cdb[1] = 0x00;	//
	cdb[2] = 0x84;	//
	cdb[3] = 0x00;	//
	cdb[4] = 0x00;	//
	cdb[5] = 0x08;	//

	memset(buffer,0x00,sizeof(buffer));
	send_mass_storage_command(handle, endpoint_out, lun, cdb, LIBUSB_ENDPOINT_IN, 10, &expected_tag);
	libusb_bulk_transfer(handle, endpoint_in, buffer, 10, &size, 5000);
	printf("   READ: received %d bytes\n", size);
	if (get_mass_storage_status(handle, endpoint_in, expected_tag) == -2) {
		get_sense(handle, endpoint_in, endpoint_out);
	} else {
		display_buffer_hex(buffer, size);
	}

	// SCSI_DEMO : BulkOut & BulkIn
	
#define BUF_SIZE	16
	printf("Bulk Out %u bytes:\n", BUF_SIZE);
	memset(cdb, 0, sizeof(cdb));
	cdb[0] = 0xfd;	// UserCommond
	cdb[1] = 0x00;	//
	cdb[2] = 0xd0;	//
	cdb[3] = 0x00;	//
	cdb[4] = 0x00;	//
	cdb[5] = 0x10;	//
	for(i = 0; i < BUF_SIZE; i++)
	{
		buffer[i] = (i << 4) + i;
	}
	send_mass_storage_command(handle, endpoint_out, lun, cdb, LIBUSB_ENDPOINT_IN, BUF_SIZE, &expected_tag);
	libusb_bulk_transfer(handle, endpoint_out, buffer, BUF_SIZE, &size, 5000);
	printf("   READ: received %d bytes\n", size);
	if (get_mass_storage_status(handle, endpoint_in, expected_tag) == -2) {
		get_sense(handle, endpoint_in, endpoint_out);
	} else {
		display_buffer_hex(buffer, size);
	}
#undef BUF_SIZE
#define BUF_SIZE	16
	printf("Bulk In %u bytes:\n", BUF_SIZE);
	memset(cdb, 0, sizeof(cdb));
	cdb[0] = 0xfe;	// UserCommond
	cdb[1] = 0x00;	//
	cdb[2] = 0xd0;	//
	cdb[3] = 0x00;	//
	cdb[4] = 0x00;	//
	cdb[5] = 0x12;	//
	for(i = 0; i < BUF_SIZE; i++)
	{
		buffer[i] = (i << 4) + i;
	}
	send_mass_storage_command(handle, endpoint_out, lun, cdb, LIBUSB_ENDPOINT_IN, BUF_SIZE, &expected_tag);
	libusb_bulk_transfer(handle, endpoint_in, buffer, BUF_SIZE, &size, 5000);
	printf("   READ: received %d bytes\n", size);
	if (get_mass_storage_status(handle, endpoint_in, expected_tag) == -2) {
		get_sense(handle, endpoint_in, endpoint_out);
	} else {
		display_buffer_hex(buffer, size);
	}

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

#if 1
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

	endpoint_in = 0x82;	// 最高bit为1，DeviceToHost
	endpoint_out = 0x01;
	test_mass_storage(handle,endpoint_in,endpoint_out);

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