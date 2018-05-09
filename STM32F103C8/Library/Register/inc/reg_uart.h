
#ifndef _REG_UART_H_
#define _REG_UART_H_

#include "stm32f10x.h"

// Init
void reg_uart_init(void);
// Send str/hex
uint32_t reg_uart_sendstr(const uint8_t * str,uint32_t len);
uint32_t reg_uart_sendhex(const uint8_t * str,uint32_t len);

// Send/Recv Byte
void reg_uart_sendbyte(const uint8_t data);
uint8_t reg_uart_recvbyte(void);



#endif
