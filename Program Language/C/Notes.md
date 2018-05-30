# **C语言奇葩问题记录**
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