# Cortex-M3 指令集
## 指令集摘要

> 注释：
>
> 1.  尖括号<>，括起操作数的其他形式
> 2.  大括号{}括住可选操作数
> 3. 操作数列并非详尽无遗
> 4. Op2 是一个灵活的第二个操作数，可以是寄存器，也可以是常量。
> 5. 大多数指令都可以使用可选的条件代码后缀



## 程序状态寄存器 xPSR

- **APSR** 应用程序状态寄存器 （CPSR当前程序状态寄存器）
  
  > 这里面比较复杂的主要是C，仔细阅读CM3指令集手册。应该就能理解了
  
  - N 负数标志 Negative
  
    - 针对有符号数，看最高bit即可
  
  - Z 零结果标志 Zero
  
    - 看是否为0即可
  
  - C 进位/借位标志 Carry
  
    - 从解释的2^32看，表明该标志对做加法时，是针对无符号数的
  
    > A carry occurs: 
    >
    > • if the result of an addition is greater than or equal to 2^32 
    >
    > • if the result of a subtraction is positive or zero 
    >
    > • as the result of an inline barrel shifter operation in a move or logical instruction. 
  
  - V 溢出标志 oVerflow
  
    - 看到该标志提到了bit[31]，我的理解是它用于判断有符号数，对吧？
  
    > Overflow occurs when the sign of the result, in bit[31], does not match the sign of the result had the operation been performed at infinite precision, for example:
    > • if adding two negative values results in a positive value
    > • if adding two positive values results in a negative value
    > • if subtracting a positive value from a negative value generates a positive value
    > • if subtracting a negative value from a positive value generates a negative value
  
  - Q 饱和标志 Saturation 【它不作为条件转移的依据】
  
    > 该标志的作用是啥？我没有太理解
    >
    > ——【网络资料】某变量达到上限or下限时被置为1
  
- **EPSR**

  - T
    - 0 表示执行ARM指令
    - 1 表示执行Thumb指令
  
- **IPSR**

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

| {cond} |           Suffix            | Tested Status Flags Description |
| :----: | :-------------------------: | :-----------------------------: |
|   EQ   |            Z set            |              equal              |
|   NE   |           Z clear           |            not equal            |
| CS/HS  |            C set            |     unsigned higher or same     |
| CC/LO  |           C clear           |         unsigned lower          |
|   MI   |            N set            |            negative             |
|   PL   |           N clear           |        positive or zero         |
|   VS   |            V set            |            overflow             |
|   VC   |           V clear           |           no overflow           |
|   HI   |      C set and Z clear      |         unsigned higher         |
|   LS   |      C clear or Z set       |     unsigned lower or same      |
|   GE   |         N equals V          |     signed greater or equal     |
|   LT   |      N not equal to V       |        signed less than         |
|   GT   |  Z clear AND (N equals V)   |       signed greater than       |
|   LE   | Z set OR (N not equal to V) |    signed less than or equal    |
|   AL   |          (ignored)          |    always (usually omitted)     |



## 1. 伪指令

- **EQU** 类似于宏定义

- DCB

  > 用于分配一片连续的字节存储单元并用指定的数据初始化

- DCW

  > 用于分配一片连续的半字(16bit)存储单元并用指定的数据初始化

- DCD

  > 用于分配一片连续的字(32bit)存储单元并用指定的数据初始化

- LDR
  - LDR	R0, =SystemInit	;这里的LDR是伪指令，它会被汇编器转换成一条“相对PC的加载指令”
  
  

## 2. 常用指令

#### 内存访问指令

- **ADR**

  > ADR指令将基于PC相对偏移的地址值读取到寄存器中 ，有范围限制

  - 0x000000a4:    a00a        ..      ADR      r0,{pc}+0x2c ; 0xd0【KEIL自带】

    > 其他都好说，只是为什么这条指令地址PC没有和流水线的概念相结合
    >
    > 0xA4 + 0x2C = 0xD0 ???

- **LDR** 
  - LDR	R1, [R2] ; 把R2所指向的内容，读取R1中
  - LDRB	r1, [r4, #0x00]   ;从地址r4+0处读取一个字节到r1

- **STR**
  
  - STR	R1,  [R0]	; 把R1的内容保存到R0所指向的空间中

  ```assembly
  ; stm32
  NVIC_IRQ_SETEN0	EQU	0xE000E100
  NVIC_IRQ0_ENABLE EQU 0x01
  ...
  LDR	R0, =NVIC_IRQ_SETEN0
  MOV	R1, #NVIC_IRQ0_ENABLE
  STR	R1, [R0]	;执行完毕该指令后,IRQ#0被使能
  ```
  
- **LDM**

  > 注意：方向和LDR的使用有所区别
  >
  > 多数据加载，将地址上的值加载到寄存器上

  -  LDMFD   SP! ,  {R0, R1, R2} ; 将堆栈中连续的3个字依次加载到寄存器R0-R2中

- **STM**

  > 多数据存储，将寄存器中的值存储到地址上
  
  ```
  格式:
  LDM{cond}  mode  Rn{!}, reglist{^}
  STM{cond}  mode  Rn{!}, reglist{^}
  其中：
      Rn：基址寄存器，装有传送数据的起始地址，Rn不允许为R15；
      ！：表示最后的地址写回到Rn中；
      reglist：可包含多于一个寄存器范围，用“，”隔开，如{R1，R2，R6-R9}，寄存器由小到大顺序排列；
      ^：不允许在用户模式和系统模式下运行
  ```

| LDM和STM的后缀              | 后缀含义                                                     |
| --------------------------- | ------------------------------------------------------------ |
| **IA:**（Increase After）   | 每次传送后地址加4,其中的寄存器**从左到右执行**,例如:STMIA R0,{R1,LR} 先存R1,再存LR |
| **IB:**（Increase Before）  | 每次传送前地址加4,同上                                       |
| **DA:**（Decrease After）   | 每次传送后地址减4,其中的寄存器**从右到左执行**,例如:STMDA R0,{R1,LR} 先存LR,再存R1 |
| **DB：**（Decrease Before） | 每次传送前地址减4,同上                                       |
| **FD:**                     | 满递减堆栈 (每次传送前地址减4)                               |
| **FA:**                     | 满递增堆栈 (每次传送后地址减4)                               |
| **ED:**                     | 空递减堆栈 (每次传送前地址加4)                               |
| **EA:**                     | 空递增堆栈 (每次传送后地址加4)                               |

- **POP**

- **PUSH**

  > 把若干寄存器的值压入堆栈中

  ```assembly
  ;子程序入口
  PUSH {R0-R3, LR} ;将R0-R3以及LR压入栈中，压栈顺序为Rm,m越大越先被压入栈中
  … 
  ;子程序出口
  POP {R0-R3, PC}
  ```

  

#### 通用数据处理指令

- **MOV**
  
  - MOV	R1, #NVIC_IRQ_SETEN0	;把立即数传送到指令中
  
- **MVN**

  > 传送取反的值

  - MVN r0, #0x01000000

  > [Thumb指令] ——仅支持R0-R7
  >
  > 更新N，Z

  - MVN Rd,Rm
- STRB(Byte=8bit)和STRH(Harf-Word=16bit)理解就行，不再重复解释
  
- **ADD**

  - ADD R2, R1, R3                 ;R2=R1+R3
  - ADD R0, R1, #256
  - ADD R0, R2, R3, LSL#1     ; R0 = R2 + (R3 << 1) 

- **ADC**

  > 计算加的时候，要加上上一次运算的进位

- **SUB**

- **SBC**

- **RSB**  {条件}{S} 目的寄存器，操作数1，操作数2 

  >  逆向减法指令，用于把操作数2减去操作数1，并将结果存放到目的寄存器中。 

- **TST**

  -  把一个寄存器的内容和另一个寄存器的内容或立即数进行**按位的与运算** 

#### 分支和控制指令

- **B** 

  - B Lable

  ```assembly
  ; example1
  ; keil: c -> switch
  CMP	r0,#0x02
  BEQ 0x000019C
  
  ;example2
  CMP r4,r0
  BCC 0x00000AC6		; [r4] < [r0]时进行跳转
  					; 常见于for循环中
  ;2019.11.04
  ; 但是逻辑不对呀，若r4<r0，也即[r4]-[r0]<0,因此是需要借位的，此时C应该为1呀，那么BCC条件就不成立了。那么怎么会跳到0x00000AC6呢？
  ;2019.11.05 终于理解了
  ;查看了CM3手册之后吗，发现C标志置位的方式有点非人类呀，居然是当[r4]>=[r0]时，C才置位。（当时为什么要这样设计？我不太理解，可能还需要从数电的角度理解下吧。以后有机会理解了之后，要在这里继续做个备注哦^_^）
  ;这样上述代码终于解释通了,CMP指令对比的方式，本质是做减法。只不过结果不保存。
  ;其中上述[r4]<[r0]的时候，N=1，C=0，Z=0 （实测）
  ;当[r4]=[r0]时，N=0,C=1,Z=1 （实测）
  ;当[r4]>[r0]时，N=0,C=1,Z=0 （我的预期）
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

- **IT**

  > If-Then condition instruction