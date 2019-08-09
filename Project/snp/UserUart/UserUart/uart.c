
#include "uart.h"
#include <stdio.h>

HANDLE hCom;

#define UART_BUF_SIZE_MAX	1024

/**
 * @brief �򿪴���
 */
bool uart_open(uint8_t com)
{
	char serial_name[128];
	DCB dcb = { 0 };
	bool ret;
	
	COMMTIMEOUTS time_outs;
	DWORD error_flag;
	COMSTAT com_start;

	if (com < 10)
	{
		sprintf(serial_name, "COM%d", com);
	}
	else
	{
		sprintf(serial_name, "\\\\.\\COM%d", com);
	}

	hCom = CreateFile(serial_name,
		GENERIC_WRITE | GENERIC_READ,					//�������д
		0,												//��ռ��ʽ
		NULL,
		OPEN_EXISTING,									//�򿪶����Ǵ���
		0,												//ͬ������
		// FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,	//�ص���ʽ
		NULL);

	if (hCom == INVALID_HANDLE_VALUE)
	{
		printf("����[%s]�򿪡���ʧ��\n", serial_name);
		return false;
	}
	else
	{
		printf("----- ����[%s]�򿪳ɹ� -----\n", serial_name);
	}

	// ��ȡ����״̬
	ret = GetCommState(hCom, &dcb);
	if (ret == false)
	{
		printf("��ȡ����[%s]״̬����ʧ��\n", serial_name);
		goto uart_end;
	}

	// ��������
	dcb.BaudRate = 115200;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;

	ret = SetCommState(hCom, &dcb);
	if (ret == false)
	{
		printf("���ô���[%s]״̬����ʧ��\n", serial_name);
		goto uart_end;
	}

	// ָ�����ڵ�ͨѶ����
	// ���뻺������1024 Bytes
	// �����������1024 Bytes
	SetupComm(hCom, UART_BUF_SIZE_MAX, UART_BUF_SIZE_MAX);

	// ���ô��ڳ�ʱ����
	time_outs.ReadIntervalTimeout = 1;			// 
	
	// ��ÿ�ζ�������ʱ���� = ��ֵ * ���ζ�ȡ���ֽ�����
	time_outs.ReadTotalTimeoutMultiplier = 1;		// ��ȡÿ�ַ���ĳ�ʱms
	time_outs.ReadTotalTimeoutConstant = 3;			// һ�ζ�ȡ�������ݵĹ̶���ʱ

	time_outs.WriteTotalTimeoutMultiplier = 1;		// д��ÿ�ַ���ĳ�ʱ
	time_outs.WriteTotalTimeoutConstant = 3;		// һ��д�봮�����ݵĹ̶���ʱ
	ret = SetCommTimeouts(hCom, &time_outs);
	if (ret == false)
	{
		printf("���ô��ڳ�ʱ����ʧ��\n");
		goto uart_end;
	}

	//��ջ�����
	ret = PurgeComm(hCom, PURGE_RXCLEAR);
	if (ret == false)
	{
		printf("��ջ���������ʧ��\n");
		goto uart_end;
	}
	ret = ClearCommError(hCom, &error_flag, &com_start);
	if (ret == false)
	{
		printf("���Ӳ����ͨѶ�����Լ���ȡͨѶ�豸�ĵ�ǰ״̬����ʧ��\n");
		goto uart_end;
	}

	return true;

uart_end:
	CloseHandle(hCom);
	return false;
}

/**
 * @brief �رմ���
 */
void uart_close(void)
{
	CloseHandle(hCom);
}

/**
 * @brief ���ڷ���
 */
bool uart_write(uint8_t * sbuf, uint32_t slen)
{
	DWORD write_len;
	uint8_t temp;

	// 1. ��������ͷ 0x55
	temp = 0x55;
	if (true != WriteFile(hCom, &temp, 1, &write_len, NULL))
	{
		return false;
	}
	if (write_len != 1)
	{
		return false;
	}

	// 2. ���ͳ����ֶΣ��ݶ�һ�ֽڣ�
	temp = slen & 0xFF;
	if (true != WriteFile(hCom, &temp, 1, &write_len, NULL))
	{
		return false;
	}
	if (write_len != 1)
	{
		return false;
	}

	// 3. ����ʵ������
	if (true != WriteFile(hCom, sbuf, slen, &write_len, NULL))
	{
		return false;
	}
	if (write_len != slen)
	{
		return false;
	}

	return true;
}


/**
 * @brief ���ڽ���
 */
bool uart_read(uint8_t * rbuf, uint32_t * rlen)
{
	DWORD read_len;

	if (true != ReadFile(hCom, rbuf, UART_BUF_SIZE_MAX + 1, &read_len, NULL))
	{
		printf("read error ?\n");
		return false;
	}
	*rlen = read_len - 2;
	memmove(rbuf, rbuf + 2, *rlen);
	if (*rlen == UART_BUF_SIZE_MAX + 1)
	{
		return false;
	}

	return true;
}
