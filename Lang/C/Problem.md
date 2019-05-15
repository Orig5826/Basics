# **C语言奇葩问题记录**
`2018.04.27 by jianfeng`

## **移位问题**
- << 右值是负数，或者右值大于左值的最大位数
	> VS2010中，在测试unsigned int类型时，出现过左移-1相当于右移1bit的情况。(似乎是偶尔发生?我也忘记了)但最好不要这样使用。移植到其他平台可能出错。MSDN如下解释。
	```
	[MSDN] The result is undefined if the right operand of a shift expression is negative or if the right operand is greater than or equal to the number of bits in the (promoted) left operand.
	```

## **默认类型转换**
- "运算和比较"的默认类型转换
	1. 例如：
		```c
		short a = 0;
		unsigned char b = 0;
		a = a + (b - 15) * 2;
		```
	
		- 运算的结果，和我们想象中是一样的，b-15会得到一个负数，然后参与运算
		> 若b = b - 15 这种情况，则b永远都是一个正数。
		> 
		> 与此类似的有，b--，--b，b++，++b。这个递减/增的操作，通常在for等循环中出现，这种情况下，就需要考虑该变量是有符号还是没有符号，需要重点考虑一些边界等问题。


	2. 例如：
		```c
		unsigned int a = 0;
		int b = 0;
		if(b - 15 > a)
		{
			printf("QQQ");
		}
		else
		{
			printf("HHH");
		}
		```
		- 结果输出为：QQQ
		> 为什么呢？因为当同一个等级出现有符号和无符号进行对比的时候，就直接切换为无符号进行对比了。若想要你原本想要的结果，则可以：
		```c
		unsigned int a = 0;
		int b = 0;
		if(b - 15 > (int)a)
		{
			printf("QQQ");
		}
		else
		{
			printf("HHH");
		}
		```
		- 结果输出为：HHH

## **sizeof数组自身**
- 代码示例如下
```c
unsigned char config[] =
{
	0x09,0x02,
	sizeof(config),
	0x55,0xaa
};
```
- 此时，你认为数组config的第三个元素的值为多少？
	- VS2017,直接报错处理
		> 报错也好，省得不同的编译器处理不用，而导致移植性差。
	- CodeWarrior,在代码运行后，第三个元素赋值为2。
		> 这当然和我原本的目的不一致了，似乎该编译器把sizeof所在的偏移作了当前的数组大小。
- **[建议] 若在数组中需要计算自身大小，建议定义数组时，就显式的指明数的大小**
	> 经测试，VS2010和CodeWarrior现象一致。
```c
unsigned char config[5] =
{
	0x09,0x02,
	sizeof(config),
	0x55,0xaa
};
```

## **浮点数的对比问题**
- [百度百科 : IEEE二进制浮点数算术标准(IEEE 754)](https://zhidao.baidu.com/question/409730820.html)
	> 符点数是采用二进制科学计数法来进行存储的，因此，绝大多数的浮点数在计算机中是不能精确表示的。
```c
#include <stdio.h>
#include <math.h>

void main()
{
	double a = 0.1 + 0.2;
	double b = 0.3;
	printf("----- 测试平台VS2017 x86 -----\n");
	printf("\ta = %f, b = %f\n", a, b);
	if (a == b)
	{
		printf("对比结果: a == b\n");
	}
	else
	{
		printf("对比结果: a != b\n");
	}
#define PRECISION		"17"	//"2"
	printf("> 提高精度来显示，查看a和b值的区别:\n");
	printf("\ta = %."PRECISION"f, b = %."PRECISION"f\n", a, b);

	/*
		浮点数比较方法
	*/
	if (fabs(a - b) < 0.000001)	//设置了比较的精度，类似于约等于
	{
		printf("对比结果: a - b == 0\n");
		printf("> 通过这种方式，认为浮点数a和b相等\n");
	}
	else
	{
		printf("对比结果: a - b != 0\n");
	}
}
```

## #ifdef 使用注意点
- #define 宏定义是不跨文件的
	- 记录一下我犯过的错误
	```c
	// 在a.c中使用了
	#ifdef DEF_A
	//Program A
	#else
	// Program B
	#endif
	// 结果我的DEF_A在某个头文件中被定义，但在a.c中我忘记了包含该定义
	// 由于codewarrior编译器即便不再同一个文件中且头文件没有直接包含，也能跳转
	// 导致我以为执行的代码是正确的，但是实际现象却不对。令人疑惑
	```
	> 因此为了避免类似的问题：注意以下两点
		1. 若在代码中使用到了#ifdef 或者#ifndef 等预编译时，需要留心一下
		2. 可以考虑使用更加高级的代码编辑器来编写代码(例如vscode)
			> 经过测试sourceinsight4 宏定义识别也不是很智能，不再同一个文件（或者包含）的情况下，其自动识别之后，对于任意文件都有效。因此不能避免该问题。所以使用SI4的时候也需要小心，它也不是万能的。
	- 例如在aaa.h中使用了bbb.h中的宏定义
	```c
	// 1.若bbb.h头文件要放在aaa.h中，则无所谓不用考虑宏定义问题
	// 当然aaa.c中需要包含aaa.h

	// 2.若bbb.h文件放在aaa.c，则需要考虑宏定义是何时被引用的
	// 则需要保证，宏定义的定义一定要在其被引用之前

	#include "aaa.h"
	#include "bbb.h"	// 若替换位置，则会出现问题
						// 若仅仅是define的定义被调用，那编译器还能给找出
						// 若是被#ifdef...#else...#endif则某些情况下，出现问题都不容易被发现
	...(aaa.c文件中其他代码)
	```