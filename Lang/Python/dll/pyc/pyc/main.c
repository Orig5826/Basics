#include <stdio.h>
#include <Python.h>
#pragma comment(lib,"python37.lib")

#include "arith.h"

/*
	实现C调用Python脚本中的函数接口
 */
void pyc_SimpleDemo(wchar_t * argv[])
{
	//Py_SetProgramName(argv[0]);
	/*
		\breaf 初始化python解释器

		若Py_Initialize失败，报错:ImportError:Nomodulenamedsite
		可能是因为没有将python相关的路径添加到环境变量中去
		或者也不添加环境变量，直接调用Py_SetPythonHome来指定python路径也行
	*/
	Py_Initialize();

	PyRun_SimpleString("print('Hello world!')");

	for (int i = 0; i <= 100; i>=10?i+=10:i++)
	{
		printf("%4d! = ", i);
		factorial(i);
	}

	/*
		释放由python解释器所分配的内存
	*/
	Py_Finalize();
}

int main(int argc, wchar_t * argv[])
{
	pyc_SimpleDemo(argv);
	return 0;
}
