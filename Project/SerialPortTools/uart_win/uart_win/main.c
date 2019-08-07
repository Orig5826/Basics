
#include <stdio.h>
#include "uart.h"

void display(uint8_t * data, uint32_t len)
{
	uint32_t i;
	for (i = 0; i < len; i++)
	{
		if (i != 0 && i % 16 == 0)
		{
			printf("\n");
		}
		printf("%02x ", *(data + i));
	}
	printf("\n");
}

int main(int argc, char * argv[])
{
	uint8_t sbuf[128] = { 0x00,0x84,0x00,0x00,0x20 };
	uint8_t rbuf[128];
	uint32_t rlen;
	
	if (true != uart_open(1))
	{
		return 0;
	}

	Sleep(100);

	for (int i = 0; i < 10; i++)
	{
		if (true != uart_write(sbuf, 5))
		{
			printf("´®¿ÚÐ´ÈëÊ§°Ü£¡\n");
			continue;
		}
		display(sbuf, 5);
		if (true != uart_read(rbuf, &rlen))
		{
			printf("´®¿Ú¶ÁÈ¡Ê§°Ü£¡\n");
			system("pause");
		}
		display(rbuf, rlen);
	}

	uart_close();
	return 0;
}
