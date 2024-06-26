
#include <stdio.h>
#include <stdlib.h>
#include "usb_drive.h"

#include <windows.h>

#if 0
// 控制台相关操作
// 控制字体颜色显示
#define SET_FORECOLOR(x) (FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | (x) | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED)
#define SET_DEFAULTCOLOR() (BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED)

#define SET_CMD_RED()		( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_FORECOLOR(FOREGROUND_RED)) )
#define SET_CMD_BLUE()		( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_FORECOLOR(FOREGROUND_BLUE)) )
#define SET_CMD_PURPLE()	( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_FORECOLOR(FOREGROUND_RED | FOREGROUND_BLUE)) )
#define SET_CMD_DEFAULT()	( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_DEFAULTCOLOR()) )
#else

#define SET_FORECOLOR(x)    
#define SET_DEFAULTCOLOR()  

#define SET_CMD_RED()        
#define SET_CMD_BLUE()       
#define SET_CMD_PURPLE()     
#define SET_CMD_DEFAULT()

#endif

#define GET_STR_DISP(x) {\
len = sizeof(str);\
USB_HID_GetString(str, len, ##x);\
	printf("["#x"]:\n\t\t%S\n",(PWSTR)str); /* %S 似乎是windows上用于显示wchar_t的*/ \
}

void Display(unsigned char * data, unsigned int len)
{
	for (unsigned int i = 0; i < len; i++)
	{
		if (i != 0 && i % 16 == 0)
		{
			printf("\n");
		}
		printf("%02x ", *(data + i));
	}
	printf("\n");
}


static unsigned int str2hex(char * str)
{
	int len = strlen(str);
	int i = 0;
	unsigned int ret = 0;
	unsigned char temp = 0;

	// 全部转化为小写处理
	for (i = 0; i < len; i++)
	{
		str[i] = (char)tolower(str[i]);
	}

	// 过滤掉0x
	if (str[0] == '0' && (str[1] == 'x'))
	{
		str += 2;
		len -= 2;
	}
	else
	{
		printf("配置文件hex表达错误！\n");
	}

	for (i = 0; i < len; i++)
	{
		// 注意上面都切换未小写了，因此此处应该减去0x61
		temp = (str[i] > 0x39) ? (str[i] - 0x61 + 0x0a) : (str[i] - 0x30);
		ret |= temp << (4 * (len - 1 - i));
	}
	return ret;
}

//
// \breaf 通过配置文件PID和VID选择当前的设备
//
enum _CfgStatus
{
	ITEM,
	VALUE,
}CfgStatus;
#define FILENAME  "hid_cfg"
void GetHIDConfig(HID_Config * pHid_cfg)
{
	FILE * pf;
	char * rBuf;
	int rLen = 0;
	int i = 0,j = 0,k = 0;
	char item[64];
	char value[64];

	pf = fopen(FILENAME, "r+");
	if (NULL == pf)
	{
		char * attr = "PID=0x084B\nVID=0x4853\n";
		pHid_cfg->PID = 0x084B;
		pHid_cfg->VID = 0x4853;

		//如果打开失败，则重新创建
		//printf("Open %s failed!\n", FILENAME);
		pf = fopen(FILENAME, "w");
		if (NULL == pf)
		{
			printf("Create %s failed!\n", FILENAME);
			return;
		}
		fwrite(attr,1,strlen(attr),pf);
		return;
	}

	fseek(pf, 0, SEEK_END);
	rLen = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	rBuf = (char *)malloc(rLen * sizeof(char));
	fread(rBuf, sizeof(char), rLen, pf);
	fclose(pf);

	CfgStatus = ITEM;
	while (i < rLen)
	{
		switch (CfgStatus)
		{
		case ITEM:
		{
			if (rBuf[i] == '=')
			{
				item[j] = '\0';
				j = 0;
				CfgStatus = VALUE;
			}
			else
			{
				item[j] = rBuf[i];
				j++;
			}
		}break;
		case VALUE:
		{
			if (rBuf[i] == '\n')
			{
				value[k] = '\0';
				k = 0;
				CfgStatus = ITEM;


				// 给hid_cfg赋值
				if (0 == strcmp(item, "PID"))
				{
					pHid_cfg->PID = (USHORT)str2hex(value);
				}

				if (0 == strcmp(item, "VID"))
				{
					pHid_cfg->VID = (USHORT)str2hex(value);
				}
			}
			else
			{
				value[k] = rBuf[i];
				k++;
			}
		}break;
		default:
		{

		}break;
		}
		i++;
	}
}

int __cdecl main()
{
	unsigned char sBuf[512];
	unsigned int sLen = 0;
	unsigned char rBuf[512];
	unsigned int rLen = 0;
	unsigned char str[512];
	unsigned int len = 0;
	int i = 0;
	unsigned short num = 0x00;

	SET_CMD_BLUE();
	usb_hid_test();

	HID_Config hid_cfg;
	//从文件中读取数据
	GetHIDConfig(&hid_cfg);

	if (TRUE == USB_HID_Connect(&hid_cfg))
	{
		// 获取厂商信息
		GET_STR_DISP(GET_MANUFACTURE);
		// 获取产品
		GET_STR_DISP(GET_PRODUCT);
		// 获取序列号
		GET_STR_DISP(GET_SERIALNUM);

#define PACKAGE_COUNT 1
		while (1)
		{
			for (i = 0; i < 512; i++)
			{
				sBuf[i] = (unsigned char)(num + i) & 0xff;
			}

#if 1
			sLen = 248;
			USB_HID_SetFeature(0, sBuf, sLen);
			rLen = 248;
			USB_HID_GetFeature(0, rBuf, &rLen);
#else
			for (int j = 0; j < PACKAGE_COUNT; j++)
			{
				// SetFeature
				// sLen = 0x40;
				sLen = 248;
				// sLen = 256;
				USB_HID_SetFeature(0, sBuf, sLen);

				//SET_CMD_RED();
				//printf("[SetFeatue] \n");
				//SET_CMD_DEFAULT();
				//Display(sBuf, sLen);
			}
			for (int j = 0; j < PACKAGE_COUNT; j++)
			{
				// GetFeatue
				// rLen = 0x40;
				rLen = 248;
				// rLen = 256;
				USB_HID_GetFeature(0, rBuf, &rLen);

				//SET_CMD_PURPLE();
				//printf("[GetFeatue] \n");
				//SET_CMD_DEFAULT();
				//Display(rBuf, rLen);
			}


			// 写入数据
			sLen = 0x40;
			USB_HID_Write(0, sBuf, sLen);

			SET_CMD_RED();
			printf("[Write] \n");
			SET_CMD_DEFAULT();
			Display(sBuf, sLen);

			// 读取数据
			rLen = 0x40;
			USB_HID_Read(0, rBuf, &rLen);

			SET_CMD_PURPLE();
			printf("[Read] \n");
			SET_CMD_DEFAULT();
			Display(rBuf, rLen);
#endif
			num++;
			// Sleep(1000);
			printf("num = %d\n",num);
	
		}
	}

	USB_HID_Close();

	system("pause");
	return 0;
}

/**
可参考HID报告描述符
#define FEATURE_LEN		248

	0x06, 0x00, 0xFF, //Usage Page:
	0x09, 0x01, //Usage: Undefined
	0xa1, 0x01, //Collection

	0x09, 0x03, //Usage (vendor-defined)
	0x15, 0x00, //Logical Minimum
	0x25, 0xFF, //Logical Maximum
	0x95, FEATURE_LEN, //Report Count
	0x75, 0x08, //Report Size
	0x81, 0x02, //Input (Data, Variable, Absolute,Buffered Bytes)

	0x09, 0x04, //Usage (vendor-defined)
	0x15, 0x00, //Logical Minimum
	0x25, 0xFF, //Logical Maximum
	0x95, FEATURE_LEN, //Report Count
	0x75, 0x08, //Report Size
	0x91, 0x02, //Output (Data, Variable, Absolute,Buffered Bytes)

	0x09, 0x05, //Usage (vendor-defined)
	0x15, 0x00, //Logical Minimum
	0x25, 0xFF, //Logical Maximum
	0x95, FEATURE_LEN, //Report Count
	0x75, 0x08, //Report Size
	0xb1, 0x02, //Feature (Data, Variable, Absolute,Buffered Bytes)

	0xc0        //End Collection
*/