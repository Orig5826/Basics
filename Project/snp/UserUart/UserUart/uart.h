
#ifndef _UART_H_
#define _UART_H_

#undef UNICODE

#include <stdint.h>
#include <windows.h>

typedef enum _bool
{
	false = 0,
	true = !false
}bool;

bool uart_open(uint8_t com);
void uart_close(void);
bool uart_write(uint8_t * sbuf, uint32_t slen);
bool uart_read(uint8_t * rbuf, uint32_t * rlen);

#endif
