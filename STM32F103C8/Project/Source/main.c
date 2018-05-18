#include "stm32f10x_conf.h"
#include "demo.h"

int main(void)
{
	#ifdef _REG_INTR_DEMO_
	tim_intr_demo();
	#else
	Timer_Example();
	#endif
	return 0;
}
