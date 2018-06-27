*STM32F103C8T6 笔记*
=================================================
`2017.2.18 by jianfeng`

## **设备基础**
1. Data Sheet
	- x4和x6 -> Low-density devices
	- x8和xB -> Medium-density devices
	- xC和xD和xE -> High-density devices
	- 除了FLash和RAM的差别之外，外设种类和数量也有所不同，详细请查看文档
	- 从数据手册中查到：
		- 20K SRAM
		- 48pins, 64K Flash Memory, LQFP, -40~105℃
			>**stm32f103c8t6**

2. Flash Memory -> PM0075 Programming manual
	- 在官网下载
		>**路径**
		>
		>HOME->Microcontrollers(in Products) -> 选择STM32F1,
		然后输入stm32f103c8,然后进相应的网页,找到Programming Manuals即可


--------------------------------------------------------------------
## **笔记整理**
- **GPIO**
	1. 输出配置的speed，是指输出驱动电路的响应速度
		>芯片内部在I/O口的输出部分安排了多个响应速度不同的输出驱动电路，用户可以根据自己的需要选择合适的驱动电路，通过选择速度来选择不同的输出驱动模块，达到最佳的噪声控制和降低功耗的目的。频率越高，噪声越高，功耗也越高。一般用低频，提高EMI性能。但若使用诸如SPI接口，18M或9M波特率，则不使用2MHz,或者10MHz的输出速度。防止信号失真
	2.  ODR BSRR BRR 为什么针对一个输出0/1的引脚，用这么多的寄存器
		> 使用BSRR和BRR改变引脚状态，没有被中断打断的风险
		- 例1：
			- ODR |= 0x80; ODR &= 0x80;		//1->0,切换为汇编变为多条语句
			- BSRR = 0x80; BRR = 0x80;		//该寄存器特点是写0无效。因此更快
		- 例2：
			- GPIOE->BSRR = 0x00400080;		//对某一引脚置位，同时清另一引脚
			- GPIOE->BSRR = 0x80; GPIOE->BRR = 0x40;
- **定时器**
	- 无论向上或者向下计数，范围都是：0 - 自动加载值。
- **UART**
	1. 非中断的情况下接收数据，一直等不到RXNE标识到来，会卡死在循环中
	> 经过查看和分析，确认RX引脚，需要配置为Floating Input。我之前的错误原因是将RX引脚配置为和TX一样了(Alternate function output Push-pull)
	> 因此接收不到数据

- **NVIC 中断控制** Nested Vectored Interrupt Controller
	- **ISER** Interrupt Set Enable Register
		> 中断使能寄存器 CM3有256个中断，由8个32位寄存器控制，写1有效
	- **ICER**Interrupt Clear Enable Register
		> 中断清除使能寄存器，写1有效
	- **ISPR** Interrupt Set Pending Register
		> 中断挂起寄存器组，将正在执行的中断挂起，而执行同级或更高级别的中断。写1有效
	- **ICPR** Interrupt Clear Pending Register
		> 中断清除挂起寄存器,写1有效
	- **IABR** Interrupt Active bit Register
		> 激活标志位寄存器组,若为1表示该位正在被执行。通过该位判断当前正在执行的中断。中断执行完毕，硬件清零
	- **IP** Interrupt Priority Register
		> 中断优先级控制寄存器,240个8位寄存器，STM32只有60个(IP[59]-IP[0]),每个中断8位中，只占用高4位。该4位又分为抢占式优先级和响应式优先级。而而这两个优先级各占几个字节，又要根据SCB->AIRCR寄存器的bit[10:8]位来定义
		- 优先级高的抢占可以打断优先级低的，但响应优先级高的不能打断优先级低的
		- 若两个中断抢占和响应优先级均一样，则数值越小，优先级越高
	- **STIR**
		> ?
- **SCB** System Control Block
	- **VTOR** Vector Table Offset Regester
		> 中断向量表，偏移配置
	- **AIRCR**
		> Application Interrupt and Reset Control Register
		- 配置抢占式优先级和响应式优先级，可以参见上面IP寄存器的介绍
		- 比如：STM32F103C8T6
			- 4bit有效，即仅有16层中断嵌套。
			- 左端靠齐，因此是高4bit有效
			- 

```
	[记录]2018.5.17 by jianfeng
	还是不能很好的理解，中断机制
	我觉得3部分最\难理解：
	1. FLASH(暂时已经理解，且写下简单的Demo)  2. 中断(部分理解，但未能实现代码)  3.DMA（完全不懂）
```

--------------------------------------------------------------------
## **MDK-ARM**
- 将函数或者变量放置到绝对地址
```
	const int gValue __attribute__((section(".ARM.__at_0x5000"))) = 3;
```



--------------------------------------------------------------------
## **问题小结**
- STM32F10X_MD定义问题
	> Keil5 创建对应工程的时候，似乎stm32 不同的工程在选择芯片之后，就进行了定义，但却无从查找。例如：我创建了stm32f103c8就自带了STM32F10X_MD该定义。