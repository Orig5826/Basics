#include "stm32f10x_conf.h"
#include "demo.h"
#include <stdio.h>

int main(void)
{
	#ifdef _REG_INTR_DEMO_
	//tim_intr_demo();
	uart1_demo();
	#else
	Timer_Example();
	#endif
	return 0;
}
