
#ifndef _I2C_SLAVE_H_
#define _I2C_SLAVE_H_

/*------------------------------------------------
 				1.	头文件
------------------------------------------------*/
#include "stm32f10x_conf.h"


void i2c_slave_init(uint8_t addr);
void i2c_slave_send(uint8_t * data, uint32_t len);
void i2c_slave_recv(uint8_t * data, uint32_t len);
void i2c_slave_example(void);


#endif

