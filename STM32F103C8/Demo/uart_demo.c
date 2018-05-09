
#include "demo.h"

void uart1_demo(void)
{
	uint8_t sBuf[9] = "\x1f\x2e\x3d\x4c\x5b\x6a\x79\x80";
	reg_uart_init();
	while(1)
	{
		reg_gpio_delay(100);
		if(10 != reg_uart_sendstr((const uint8_t *)"UART OK!\r\n",12))
		{
			reg_uart_sendstr((const uint8_t *)"retLen != needLen!\r\n",0);
		}
		reg_uart_sendhex(sBuf,8);
	}
}

void uart1_shell_demo(void)
{
	uint8_t temp = 0x55;
	reg_uart_init();
	reg_uart_sendstr((const uint8_t *)"uart1_shell_demo\r\n",0);

	while(1)
	{
		temp = reg_uart_recvbyte();
		reg_uart_sendbyte(temp);
	}
}
