
#include <stdio.h>
#include <stdlib.h>
#include "usb_demo.h"
#include "usb_drive.h"

#include <windows.h>

// ����̨��ز���
// ����������ɫ��ʾ
#define SET_FORECOLOR(x) (FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | (x) | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED)
#define SET_DEFAULTCOLOR() (BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED)

#define SET_CMD_RED()		( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_FORECOLOR(FOREGROUND_RED)) )
#define SET_CMD_BLUE()		( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_FORECOLOR(FOREGROUND_BLUE)) )
#define SET_CMD_PURPLE()	( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_FORECOLOR(FOREGROUND_RED | FOREGROUND_BLUE)) )
#define SET_CMD_DEFAULT()	( SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SET_DEFAULTCOLOR()) )

#define GET_STR_DISP(x) {\
len = sizeof(str);\
USB_HID_GetString(str, len, ##x);\
printf("["#x"]:\n\t\t%S\n",(PWSTR)str); /* %S �ƺ���windows��������ʾwchar_t��*/ \
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

	// ȫ��ת��ΪСд����
	for (i = 0; i < len; i++)
	{
		str[i] = (char)tolower(str[i]);
	}

	// ���˵�0x
	if (str[0] == '0' && (str[1] == 'x'))
	{
		str += 2;
		len -= 2;
	}
	else
	{
		printf("�����ļ�hex������\n");
	}

	for (i = 0; i < len; i++)
	{
		temp = (str[i] > 0x39) ? (str[i] - 0x41) : (str[i] - 0x30);
		ret |= temp << (4 * (len - 1 - i));
	}
	return ret;
}

//
// \breaf ͨ�������ļ�PID��VIDѡ��ǰ���豸
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

		//�����ʧ�ܣ������´���
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


				// ��hid_cfg��ֵ
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
	unsigned char sBuf[0x40];
	unsigned int sLen = 0;
	unsigned char rBuf[0x40];
	unsigned int rLen = 0;
	unsigned char str[64];
	unsigned int len = 0;
	int i = 0;
	unsigned short num = 0x00;

	SET_CMD_BLUE();
	usb_hid_test();

	HID_Config hid_cfg;
	//���ļ��ж�ȡ����
	GetHIDConfig(&hid_cfg);

	if (TRUE == USB_HID_Connect(&hid_cfg))
	{
		// ��ȡ������Ϣ
		GET_STR_DISP(GET_MANUFACTURE);
		// ��ȡ��Ʒ
		GET_STR_DISP(GET_PRODUCT);
		// ��ȡ���к�
		GET_STR_DISP(GET_SERIALNUM);

		while (1)
		{
			for (i = 0; i < 64; i++)
			{
				sBuf[i] = (unsigned char)(num + i) & 0xff;
			}

			sLen = 0x40;
			USB_HID_Write(0, sBuf, sLen);
			rLen = 0x40;
			USB_HID_Read(0, rBuf, &rLen);

			SET_CMD_PURPLE();
			printf("[Read] \n");
			SET_CMD_DEFAULT();
			Display(rBuf, rLen);

			if (0 != memcmp(sBuf, rBuf, sLen))
			{
				SET_CMD_RED();
				printf("[Write] \n");
				SET_CMD_DEFAULT();
				Display(sBuf, sLen);
				printf("[ERROR] --- ��д��һ�� ---\n\n");
				break;
			}

			Sleep(1000);
			num++;
			printf("------------------------\n");
		}
	}

	USB_HID_Close();

	system("pause");
	return 0;
}
