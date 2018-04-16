
#ifndef _REG_UART_H_
#define _REG_UART_H_

#include "stm32f10x.h"

// Interface
void reg_uart_init(void);
uint32_t reg_uart_sendstr(const uint8_t * str,uint32_t len);
uint32_t reg_uart_sendhex(const uint8_t * str,uint32_t len);

#endif
