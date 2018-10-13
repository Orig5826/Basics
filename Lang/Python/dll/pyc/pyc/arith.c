/*
 * @breaf VS2017 C调用Python脚本
 *
 * 问题记录：
 * 1.报错:python37_d.lib 在Debug模式下，需要在安装python的时候安装相应的"python debug bin/library"
 *        有对应的选项，具体名称我记不住了。安装的时候如果忘记安装了，后续Modify也可以
 */
#include <Python.h>

/*
	C调用Python模块实现的接口
	
*/
int factorial(int n)
{
	PyObject * pModule, *pFun;
	PyObject *pArgs, *pValue;
	PyObject * pModuleName;

	/*
		默认情况，需要将该python脚本放在输出的exe文件目录下，才能正常被导入。
		若添加上这句，表示导入当前目录下的python脚本，即可以把脚本放在工程目录下
		方便Debug和Release调用。也方便修改python脚本
		(当然了也可以写为绝对地址)

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('F:/Code/VS2017/pyc/pyc')");
	*/
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	// 导入模块，即自己写的python脚本
	pModuleName = PyUnicode_FromString("arith");
	pModule = PyImport_Import(pModuleName);
	// pModule = PyImport_ImportModule("Apaki");
	if (pModule == NULL)
	{
		printf("导入python模块失败\n");
		return 0;
	}
	// 确定调用的函数名称
	pFun = PyObject_GetAttrString(pModule, "factorial");

	// 配置传递的参数
	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, PyLong_FromLong(n));

	// 调用函数，并且取得返回值
	pValue = PyObject_CallObject(pFun, pArgs);

	if (pValue != Py_True)
	{
		printf("返回结果无效\n");
		return 0;
	}
	// 若返回0，则失败，返回1数据正常
	return 1;
 }


double py_square(double a)
{
	return a * a;
}