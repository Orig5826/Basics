
#ifndef _UART_H_
#define _UART_H_

#include "stm32f10x_conf.h"


//---------------------------
//			API
//---------------------------
void UartInit(void);
void UartSendString(const uint8_t * str,uint32_t strlen);



#endif
