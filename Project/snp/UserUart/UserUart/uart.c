
#include "uart.h"
#include <stdio.h>

HANDLE hCom;

#define UART_BUF_SIZE_MAX	1024

/**
 * @brief 打开串口
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
		GENERIC_WRITE | GENERIC_READ,					//允许读和写
		0,												//独占方式
		NULL,
		OPEN_EXISTING,									//打开而不是创建
		0,												//同步操作
		// FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,	//重叠方式
		NULL);

	if (hCom == INVALID_HANDLE_VALUE)
	{
		printf("串口[%s]打开——失败\n", serial_name);
		return false;
	}
	else
	{
		printf("----- 串口[%s]打开成功 -----\n", serial_name);
	}

	// 获取串口状态
	ret = GetCommState(hCom, &dcb);
	if (ret == false)
	{
		printf("获取串口[%s]状态——失败\n", serial_name);
		goto uart_end;
	}

	// 串口配置
	dcb.BaudRate = 115200;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;

	ret = SetCommState(hCom, &dcb);
	if (ret == false)
	{
		printf("设置串口[%s]状态——失败\n", serial_name);
		goto uart_end;
	}

	// 指定串口的通讯参数
	// 输入缓存区：1024 Bytes
	// 输出缓存区：1024 Bytes
	SetupComm(hCom, UART_BUF_SIZE_MAX, UART_BUF_SIZE_MAX);

	// 配置串口超时参数
	time_outs.ReadIntervalTimeout = 1;			// 
	
	// （每次读操作超时总数 = 该值 * 本次读取的字节数）
	time_outs.ReadTotalTimeoutMultiplier = 1;		// 读取每字符间的超时ms
	time_outs.ReadTotalTimeoutConstant = 3;			// 一次读取串口数据的固定超时

	time_outs.WriteTotalTimeoutMultiplier = 1;		// 写入每字符间的超时
	time_outs.WriteTotalTimeoutConstant = 3;		// 一次写入串口数据的固定超时
	ret = SetCommTimeouts(hCom, &time_outs);
	if (ret == false)
	{
		printf("设置串口超时——失败\n");
		goto uart_end;
	}

	//清空缓冲区
	ret = PurgeComm(hCom, PURGE_RXCLEAR);
	if (ret == false)
	{
		printf("清空缓冲区——失败\n");
		goto uart_end;
	}
	ret = ClearCommError(hCom, &error_flag, &com_start);
	if (ret == false)
	{
		printf("清除硬件的通讯错误以及获取通讯设备的当前状态——失败\n");
		goto uart_end;
	}

	return true;

uart_end:
	CloseHandle(hCom);
	return false;
}

/**
 * @brief 关闭串口
 */
void uart_close(void)
{
	CloseHandle(hCom);
}

/**
 * @brief 串口发送
 */
bool uart_write(uint8_t * sbuf, uint32_t slen)
{
	DWORD write_len;
	uint8_t temp;

	// 1. 发送数据头 0x55
	temp = 0x55;
	if (true != WriteFile(hCom, &temp, 1, &write_len, NULL))
	{
		return false;
	}
	if (write_len != 1)
	{
		return false;
	}

	// 2. 发送长度字段（暂定一字节）
	temp = slen & 0xFF;
	if (true != WriteFile(hCom, &temp, 1, &write_len, NULL))
	{
		return false;
	}
	if (write_len != 1)
	{
		return false;
	}

	// 3. 发送实际数据
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
 * @brief 串口接收
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
