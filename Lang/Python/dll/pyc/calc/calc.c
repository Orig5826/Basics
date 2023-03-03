
#include <Python.h>
#pragma comment(lib,"python38.lib")

#include "calc.h"

/*
	ʵ����ع��ܵ�C����
 */
DLL_API double CALL  py_get_squre(double a)
{
	return a * a;
}



/*
	������������
	��python�ӿڲ���ת��ΪC�ӿڲ���������C�������������ص�C����ת��Ϊpython��������
	���̣�����Python���� -> ת��ΪC���� -> ����C�ӿ� -> ����C���� -> ת��Ϊpython��������
*/
static PyObject * _py_get_squre(PyObject * self, PyObject * args)
{
	double _a;
	double ret;

	if (!PyArg_ParseTuple(args, "d", &_a))
	{
		printf("PyArg_ParseTuple ��������ʧ��\n");
		return NULL;
	}
	ret = py_get_squre(_a);
	return PyFloat_FromDouble(ret);
}

/*
	Method������ calc_module_methods�������Լ������
	����pythonģ��������Щ�������Ա�����
*/
static PyMethodDef calc_module_methods[] = 
{
	{
		"py_get_squre",			//����python�����ĺ�������
		_py_get_squre,			//��������
		METH_VARARGS,			//�ú��ʾ�������䳤
		""						//һ��˵���Ե��ַ���
	},

	// �������� ... ��β
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
	�������� PyInit_calc_module(���ֲ��������"PyInit_ + ģ����")
	���������н�ģ�������뵼�����������
*/
PyMODINIT_FUNC PyInit_calc(void)
{
	PyObject *m;
	m = PyModule_Create(&calc_module);
	if (m == NULL)
	{
		printf("ģ�����ʧ��\n");
		return NULL;
	}
	// Debug
	//printf("PyInit calc_module\n");
	return m;
}
