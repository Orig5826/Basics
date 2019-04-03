# **C语言特殊笔记**
`2018.05.30 by jianfeng`

## windows平台
- DLL文件
	- LoadLibrary 加载dll，返回该动态链接库的句柄（HMODULE）
	- GetProcAddress 获取该动态链接库中函数的地址
```
/*
第一次调试，虽然现象和预期一样，但总是报错
Run-Time Check Failure #0 - The value of ESP was not properly saved across a function call.  This is usually a result of calling a function declared with one calling convention with a function pointer declared with a different calling convention.
[百度百科]
函数定义的调用规则,和实际的调用规则不同。如 编译器默认的是__cdecl，而__stdcall 类型的函数却用了 __cdecl 的调用规则，由于编译时不会报错，结果出现了运行时异常。
[理解]
函数的调用规则不同，因此在函数指针声明的时候，添加WNINAPI。解决该问题。
*/
例如：
typedef long (WINAPI * pCloseDevice)(long hDev);
```

## #define宏定义#和##的使用区别
- #
	> 主要用于参数的字符串化
	- 例如：#define _J(x)	#x
		若此时调用 _J(gbk)，则实际上是"gbk"字符串
		若这样调用 _J("gbk"),则实际上是"\"gbk\""。
		现在你理解了吗？
	- 经典用法，举例说明
		> 可以直接将宏定义中的数字转化为字符串
```
#define VER_NAME				"MJA"
#define VER_MAJOR				1
#define VER_MINOR				1		//1->k20 2->k30
#define VER_MICRO				03

#define __STR(x)				#x
#define _STR(x)					__STR(x)
#define MJA_K1_VER				(VER_NAME"_"_STR(VER_MAJOR)"."_STR(VER_MINOR)"."_STR(VER_MICRO))
```	
	- 特殊(感觉很少用) #define  _B(x)  #@x
		调用_B(1) 表示  '1'
- ##
	> 这个符号主要用于链接，使其成为一个整体
	- 在某种程度上，可以减少代码量
```
#define GETDATA(TYPE,...)\
case TYPE: \
    {\
        data=Get##TYPE(...)\
        ....\
    }break;\

调用的时候处理为：
switch(TYPE)
{
    GETDATA(TYPE,...);
}
```
若不适用##,则实际需要按照如下方式写
```
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
```
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
	{0,0,0
	}
};
```