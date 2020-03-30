# **C语言特殊笔记**
`2018.05.30 by jianfeng`

## windows平台
- DLL文件
	- LoadLibrary 加载dll，返回该动态链接库的句柄（HMODULE）
	- GetProcAddress 获取该动态链接库中函数的地址
```c
/*
第一次调试，虽然现象和预期一样，但总是报错
Run-Time Check Failure #0 - The value of ESP was not properly saved across a function call.  This is usually a result of calling a function declared with one calling convention with a function pointer declared with a different calling convention.
[百度百科]
函数定义的调用规则,和实际的调用规则不同。如 编译器默认的是__cdecl，而__stdcall 类型的函数却用了 __cdecl 的调用规则，由于编译时不会报错，结果出现了运行时异常。
[理解]
函数的调用规则不同，因此在函数指针声明的时候，添加WNINAPI。解决该问题。
如下示例：
*/
typedef long (WINAPI * pCloseDevice)(long hDev);
```

## #define宏定义#和##的使用区别
- 符号：#
	> 主要用于参数的字符串化
	- 例如：#define _J(x)	#x
		若此时调用 _J(gbk)，则实际上是"gbk"字符串
		若这样调用 _J("gbk"),则实际上是"\"gbk\""。
		现在你理解了吗？
	
	- 特殊(感觉很少用) #define  _B(x)  #@x
		
		- 例如：调用_B(1) 表示  '1'
	- 经典用法，举例说明
		
		> 可以直接将宏定义中的数字转化为字符串
```c
#define VER_NAME				"MJA"
#define VER_MAJOR				1
#define VER_MINOR				1		//1->k20 2->k30
#define VER_MICRO				03

#define __STR(x)				#x
#define _STR(x)					__STR(x)
#define MJA_K1_VER				(VER_NAME"_"_STR(VER_MAJOR)"."_STR(VER_MINOR)"."_STR(VER_MICRO))
```

- 符号：##
	> 这个符号主要用于链接，使其成为一个整体
	
	- 在某种程度上，可以减少代码量
```c
#define GETDATA(TYPE,...)\
case TYPE: \
    {\
        data=Get##TYPE(...)\
        ....\
    }break;

//调用的时候处理为：
switch(TYPE)
{
	GETDATA(TYPE,...);
}
```
```c
// 若不使用##,则实际需要按照如下方式写
switch(TYPE)
{
	case Int:
	{
		data=GetInt(...);
		...
	}break;
	case Double
	{
		data=GetDouble...);
		....
	}break;
	case U_Int:
	{
		data=GetU_Int(....);
		....
	}break;
}
```

## 结构体初始化的方式
- 结构体初始化示例(常见的初始化方式就不再此处一一列举了)
```c
typedef struct _data
{
	int flag;
	int length;
	double num;
}Data;

Data data[2] = {
	{
		.flag = 1,
		.length = 2,
		.num = 4
	},
	{
		0,0,0
	}
};
```

## 内存泄漏话题

- 指针相关概念

  - 空指针

  - 野指针

    > 未被初始化的指针

  - 悬空指针

    > 原指向的对象已经被释放了的指针。（也通常有人把悬空指针归为野指针，区分开叫我更加习惯，感觉好理解）

- 避免出现此类问题的好习惯

  1. 指针在创建之时，要么被初始化，要么被设置为NULL。（避免野指针）

  2. 通过malloc等分配空间之后，要使用if语句判断空间是否分配成功。

  3. 指针被释放之后，一定要把该指针置为NULL。（避免悬空指针）

- 指针使用相关注意点

  1. 注意指针指向对象的作用域

     ```c
     
     #include <stdio.h>
     #include <stdlib.h>
     #include <stdint.h>
     #include <string.h>
     
     char * p = NULL;
     
     void print_set()
     {
         int i = 0;
         char ch[11];
     
         for(i = 0; i < 10; i++)
         {
             ch[i] = '0' + i;
         }
         ch[i] = '\0';
         p = &ch[0];
     }
     
     void print_str()
     {
         printf("%s",p);
     }
     
     void alloc_stack_again()
     {
         int i = 0;
         char ch[8];
     
         for(i = 0; i < 7; i++)
         {
             ch[i] = 'A' + i;
         }
         ch[i] = '\0';
     }
     
     void main()
     {
         print_set();
         alloc_stack_again();
         print_str();
     }
     
     // 使用codeblocks测试结果为
     // 
     // 012ABCDEFG
     ```

     

  2. 注意已经通过malloc分配空间的指针被再复制（或者++等副作用操作）

     > 一开始想：该问题是否可以通过将需要用到malloc的变量，初始化为指针常量。
     >
     > 后来一想，不对。若不在初始化的时候malloc呢？就不行了

  3. 注意多个指针指向同一块堆空间的情况，若通过其中一个指针释放，则其他指针怎么办？

## 位域的符号问题

```c

struct _data
{
	uint32_t a:8;
	int32_t b:4;		// 有符号
	// uint32_t b:4;	// 无符号
	uint32_t c:4;
	uint32_t d:8;
	uint32_t e:8;
}data;

void main()
{
	data.b = -3;
	data.e = 0x55;
	printf("%d\n",data.b);
    printf("0x%04x",data);
}
```

如上代码，对于b，若定义为int32_t，则printf打印出来的就是-3。若定义为uint32_t则打印的结果为13。

经过查看内存中的数据，无论定义为int32_t还是uint32_t，只要复制为-3，那么内存中相应4bit的数据永远是0x0D。

// 负数 = 取反加1

比如，对于-3而言，3为0011b，取反之后为1100b，随后加1，得到结果为1101b。（若把它看成无符号数则为13）。本质上是硬件底层对于减法的一种简化处理，将减法用加法进行运算。能够简化CPU的设计。（具体原理查看数字电路技术基础）

------

以上说明的是底层原理。但是内存中的数据都是0x0D，为什么在不同的定义下会打印出不同的结果呢？

这个是由于定义的基本类型是int/uint，因此在%d打印的时候，会有个高位填充，若是无符号数，则高位用0填充。若是有符号数，则高位用1填充。