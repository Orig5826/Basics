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

- **APSR** 应用程序状态寄存器 （CPSR当前程序状态寄存器）
  - N 负数标志 Negative
  
  - Z 零结果标志 Zero
  
  - C 进位/借位标志 Carry
  
  - V 溢出标志 oVerflow
  
  - S 饱和标志 Saturation 【它不作为条件转移的依据】
  
    > 该标志的作用是啥？我没有太理解
  
- CPSR

  - T
    - 0 表示执行ARM指令
    - 1 表示执行Thumb指令
  - 

- **后缀**
  - S 要求更新APSR中的S标志，比如MOVS
  - EQ,NE,LT,GT等，有条件的执行命令

### 寄存器使用说明

- **r0 - r3**
  
> 用作传入函数参数，传出函数返回值。在子程序调用之间，可以将 r0 - r3 用于任何用途。被调用函数在返回之前不必恢复 r0 - r3。如果调用函数需要再次使用 r0 - r3 的内容，则它必须保留这些内容。

- **r4 - r11**
  
> 被用来存放函数的局部变量。如果被调用函数使用了这些寄存器，它在返回之前必须恢复这些寄存器的值。

- **r12**
  
> 是内部调用暂时寄存器 ip。它在过程链接胶合代码（例如，交互操作胶合代码）中用于此角色。在过程调用之间，可以将它用于任何用途。被调用函数在返回之前不必恢复 r12。

- **r13**
  
> 是栈指针 sp。它不能用于任何其它用途。sp 中存放的值在退出被调用函数时必须与进入时的值相同。

- **r14**
  
> 是链接寄存器 lr。如果您保存了返回地址，则可以在调用之间将 r14 用于其它用途，程序返回时要恢复

- **r15**

  > 是程序计数器 PC。它不能用于任何其它用途。

### 条件说明

> 资料源自Keil

| {cond} |Suffix                     |Tested Status Flags Description |
| :----: | :----:                    | :----:                         |
|EQ      |Z set                      |equal                           |
|NE      |Z clear                    |not equal                       |
|CS/HS   |C set                      |unsigned higher or same         |
|CC/LO   |C clear                    |unsigned lower                  |
|MI      |N set                      |negative                        |
|PL      |N clear                    |positive or zero                |
|VS      |V set                      |overflow                        |
|VC      |V clear                    |no overflow                     |
|HI      |C set and Z clear          |unsigned higher                 |
|LS      |C clear or Z set           |unsigned lower or same          |
|GE      |N equals V                 |signed greater or equal         |
|LT      |N not equal to V           |signed less than                |
|GT      |Z clear AND (N equals V)   |signed greater than             |
|LE      |Z set OR (N not equal to V)|signed less than or equal       |
|AL      |(ignored)                  |always (usually omitted)        |



## 1. 伪指令

- **EQU** 类似于宏定义

## 2. 常用指令

- **LDR** 
  - LDR	R0, =SystemInit	;这里的LDR是伪指令，它会被汇编器转换成一条“相对PC的加载指令”
  - LDRB	r1, [r4, #0x00]   ;从地址r4+0处读取一个字节到r1
  
- **MOV**
  
  - MOV	R1, #NVIC_IRQ_SETEN0	;把立即数传送到指令中
  
- MVN

  > 传送取反的值

  - MVN r0, #0x01000000

  > [Thumb指令] ——仅支持R0-R7
  >
  > 更新N，Z

  - MVN Rd,Rm

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

  ```assembly
  ;keil: c -> switch
  CMP	r0,#0x02
  BEQ 0x000019C
  ```

- **BL** （跳转前会在R14中保存PC当前值，因此可以通过将R14内容重新加载到PC中，用于返回跳转前的指令处执行。因此该指令是实现子程序调用的一个基本常用手段） ——R14也叫链接寄存器(Lr)

  > 可以简称为“带链接跳转”

  - **BL.W** 

    > KEIL中使用 W 后缀表示该指令是32位指令

- **BX**

  > **跳转并切换指令集**  若bit0=0则会切换为ARM指令。
  >
  > ？为什么会用于函数返回呢？

  - BX	lr

    > 常见用于函数返回

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

