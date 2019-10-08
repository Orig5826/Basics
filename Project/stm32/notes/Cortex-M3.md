# Cortex-M3 指令集
## 指令集摘要

> 注释：
>
> 1.  尖括号<>，括起操作数的其他形式
> 2.  大括号{}括住可选操作数
> 3. 操作数列并非详尽无遗
> 4. Op2 是一个灵活的第二个操作数，可以是寄存器，也可以是常量。
> 5. 大多数指令都可以使用可选的条件代码后缀



## 状态寄存器

- **APSR**应用程序状态寄存器 （CPSR当前程序状态寄存器）
  - N 负数标志 Negative
  - Z 零结果标志 Zero
  - C 进位/借位标志 Carry
  - V 溢出标志 oVerflow
  - S 饱和标志 Saturation 【它不作为条件转移的依据】
- **后缀**
  - S 要求更新APSR中的S标志
  - EQ,NE,LT,GT等，有条件的执行命令



## 1. 伪指令

- **EQU** 类似于宏定义

## 2. 常用指令

- **LDR** 
  - LDR	R0, =SystemInit	;这里的LDR是伪指令，它会被汇编器转换成一条“相对PC的加载指令”
  - LDRB	r1, [r4, #0x00]   ;从地址r4+0处读取一个字节到r1
- **MOV**
  - MOV	R1, #NVIC_IRQ_SETEN0	;把立即数传送到指令中
- **STR**
  - STR	R1,  [R0]	; *R0=R1

```assembly
; stm32
NVIC_IRQ_SETEN0	EQU	0xE000E100
NVIC_IRQ0_ENABLE EQU 0x01
...
LDR	R0, =NVIC_IRQ_SETEN0
MOV	R1, #NVIC_IRQ0_ENABLE
STR	R1, [R0]	;执行完毕该指令后,IRQ#0被使能
```

- **B** 

  - B Lable

- **BL** （跳转前会在R14中保存PC当前值，因此可以通过将R14内容重新加载到PC中，用于返回跳转前的指令处执行。因此该指令是实现子程序调用的一个基本常用手段） ——R14也叫链接寄存器(Lr)

- **BX**

- **BLX**

  > X 有ARM和Thumb指令的相互切换的作用吗？
  >
  > BX Rm 或 BLX Rm
  >
  > 如果 Rm 的位 [0] 为 0，则处理器的状态会更改为（或保持在）ARM 状态
  >
  > 如果 Rm 的位 [0] 为 1，则处理器的状态会更改为（或保持在）Thumb 状态

- **CBNZ** (比较，若结果非0则跳转，——只能跳转到后面的指令)

  - CBNZ     r5,0x08002C10

- **CBZ**  (比较，若结果是0则跳转，——只能跳转到后面的指令)

- **PUSH**

  > 把若干寄存器的值压入堆栈中

  ```assembly
  ;子程序入口
  PUSH {R0-R3, LR} ;将R0-R3以及LR压入栈中，压栈顺序为Rm,m越大越先被压入栈中
  … 
  ;子程序出口
  POP {R0-R3, PC}
  ```

  

  

## 3. 其他

**DCB** 

DCH

DCW

