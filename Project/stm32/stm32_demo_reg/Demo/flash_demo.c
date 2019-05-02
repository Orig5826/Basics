
#include "demo.h"

void flash_demo(void)
{
	uint32_t rBuf[8];
	uint8_t buff[32];
	reg_uart_init();
	reg_uart_sendstr("reg_uart_sendstr\r\n",0);

	reg_unlock();
	if(TRUE != reg_earse_page(0x08004000))
	{
		reg_uart_sendstr("earse page err\r\n",0);
	}
	if(TRUE != reg_program_halfword(0x08004014,0x1122))
	{
		reg_uart_sendstr("program2 err\r\n",0);
	}
	reg_lock();

	if(TRUE != reg_program_halfword(0x08004018,0x0099))
	{
		reg_uart_sendstr("program3 err\r\n",0);
	}
	reg_read_word(0x08004000,rBuf,8);
	reg_uart_sendhex((uint8_t * )rBuf,32);
	
	reg_read_byte(0x08004000,buff,32);
	reg_uart_sendhex((uint8_t * )buff,32);
	
	
	while(1)
	{
		;
	}
}
