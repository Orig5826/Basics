
#include <Python.h>
#pragma comment(lib,"python38.lib")

#include "calc.h"

/*
	实现相关功能的C函数
 */
DLL_API double CALL  py_get_squre(double a)
{
	return a * a;
}



/*
	【包裹函数】
	将python接口参数转换为C接口参数，调用C函数，并将返回的C参数转换为python参数返回
	过程：传入Python参数 -> 转换为C参数 -> 调用C接口 -> 返回C参数 -> 转换为python参数返回
*/
static PyObject * _py_get_squre(PyObject * self, PyObject * args)
{
	double _a;
	double ret;

	if (!PyArg_ParseTuple(args, "d", &_a))
	{
		printf("PyArg_ParseTuple 参数解析失败\n");
		return NULL;
	}
	ret = py_get_squre(_a);
	return PyFloat_FromDouble(ret);
}

/*
	Method导出表 calc_module_methods（名字自己随便起）
	告诉python模块里有哪些参数可以被调用
*/
static PyMethodDef calc_module_methods[] = 
{
	{
		"py_get_squre",			//给出python环境的函数名称
		_py_get_squre,			//包裹函数
		METH_VARARGS,			//该宏表示：参数变长
		""						//一个说明性的字符串
	},

	// 导出表以 ... 结尾
	{NULL, NULL, 0, NULL}
};


static struct PyModuleDef calc_module = 
{
	PyModuleDef_HEAD_INIT,
	"calc_module",
	NULL,
	-1,
	calc_module_methods
};

/*
	导出函数 PyInit_calc_module(名字不能随便起，"PyInit_ + 模块名")
	导出函数中将模块名称与导出表进行连接
*/
PyMODINIT_FUNC PyInit_calc(void)
{
	PyObject *m;
	m = PyModule_Create(&calc_module);
	if (m == NULL)
	{
		printf("模块加载失败\n");
		return NULL;
	}
	// Debug
	//printf("PyInit calc_module\n");
	return m;
}
