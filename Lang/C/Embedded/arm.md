过程调用标准

- **R0 - R3**

  > 用于传入函数参数，其中R0用于函数返回值

  - 写到这里，突然感觉没必要详细描述了。

  - 因为本质都是一样的，想尽办法保护传入和传出参数。

    > 比如KEIL是如下处理方式：
    >
    > 1. 传入参数当作局部变量，采用R4-Rx进行保护（当然了，这是取传参变量地址的的缘故，若取地址。则只能压栈了）。便于后续R0-R3作为被调用子函数的传入参数和不存在子函数的时候随便使用。
    >
    > 保护方式可能并不唯一。此处仅做示例记录。

    ```c
    void sub(int a,int b)
    {
    	int c = 0;
    	int d = 0;
    	int e = 0;
    	int f = 0;
    	// d = sub_sub(a,b,c);
    }
    ```

    ```assembly
                     sub:
    0x00002348 B570      PUSH     {r4-r6,lr}
    0x0000234A 4604      MOV      r4,r0			; 相当于看作局部变量处理 
    0x0000234C 460D      MOV      r5,r1			; 
    0x0000234E 2000      MOVS     r0,#0x00
    0x00002350 2100      MOVS     r1,#0x00
    0x00002352 2200      MOVS     r2,#0x00
    0x00002354 2300      MOVS     r3,#0x00
    0x00002356 BD70      POP      {r4-r6,pc}
    ```

    

- **R4 - R11**

  > 用来存放函数的局部变量。被调用函数中使用了谁，则需要保护谁。

  ```c
  int add_test(void)
  {
  	int a = 2;
  	int b = 3;
  	int c = 0;
  	
  	c = add(a,b);
  	return c;
  }
  ```

  Cortex-M0+ 平台KEIL编译后对应的汇编如下：

  ```assembly
                   add_test:
  0x00002290 B570      PUSH     {r4-r6,lr}
  0x00002292 2402      MOVS     r4,#0x02
  0x00002294 2503      MOVS     r5,#0x03
  0x00002296 2600      MOVS     r6,#0x00
  0x00002298 4629      MOV      r1,r5
  0x0000229A 4620      MOV      r0,r4
  0x0000229C F7FFFF50  BL.W     add (0x00002140)
  0x000022A0 4606      MOV      r6,r0
  0x000022A2 4630      MOV      r0,r6
  0x000022A4 BD70      POP      {r4-r6,pc}
  ```

- **R12**

  > 内部调用暂时寄存器IP
  >
  > ？

- **R13** (**SP**)

  > 栈指针，SP中存放的值在推出被调用函数时，必须和进入时的值相同。

  ```c
  int add_test(void)
  {
  	int a = 2;
  	int b = 3;
  	int c = 0;
  	int data[7] = {7,8,9,10,11};
  	
  	c = add(a,b);
  	return c;
  }
  ```

  

  ```assembly
                   add_test:
  0x000022C8 B570      PUSH     {r4-r6,lr}
  0x000022CA B088      SUB      sp,sp,#0x20		; 不理解为什么是0x20而不直接0x1C?
  0x000022CC 2402      MOVS     r4,#0x02
  0x000022CE 2503      MOVS     r5,#0x03
  0x000022D0 2600      MOVS     r6,#0x00
  0x000022D2 221C      MOVS     r2,#0x1C
  0x000022D4 4905      LDR      r1,[pc,#20]  ; @0x000022EC
  0x000022D6 A801      ADD      r0,sp,#0x04		; 可能和keil的编译底层有关吧？
  0x000022D8 F7FFFF38  BL.W     __aeabi_memcpy4 (0x0000214C)
  0x000022DC 4629      MOV      r1,r5
  0x000022DE 4620      MOV      r0,r4
  0x000022E0 F7FFFF2E  BL.W     add (0x00002140)
  0x000022E4 4606      MOV      r6,r0
  0x000022E6 4630      MOV      r0,r6
  0x000022E8 B008      ADD      sp,sp,#0x20
  0x000022EA BD70      POP      {r4-r6,pc}
  0x000022EC 0000      DCW      0x0000
  0x000022EE 4023      DCW      0x4023
  ```

  

- **R14** (**LR**)

  > 链接寄存器，用于存储函数返回地址。
  >
  > 若被调用函数中R14已经被压入栈中，则在被调用函数中可以将该寄存器用于其他用途。当然了，一般很少这么做。

- **R15** (**PC**)

  > 程序计数寄存器