/*
 * @breaf VS2017 C����Python�ű�
 *
 * �����¼��
 * 1.����:python37_d.lib ��Debugģʽ�£���Ҫ�ڰ�װpython��ʱ��װ��Ӧ��"python debug bin/library"
 *        �ж�Ӧ��ѡ����������Ҽǲ�ס�ˡ���װ��ʱ��������ǰ�װ�ˣ�����ModifyҲ����
 */
#include <Python.h>

/*
	C����Pythonģ��ʵ�ֵĽӿ�
	
*/
int factorial(int n)
{
	PyObject * pModule, *pFun;
	PyObject *pArgs, *pValue;
	PyObject * pModuleName;

	/*
		Ĭ���������Ҫ����python�ű����������exe�ļ�Ŀ¼�£��������������롣
		���������䣬��ʾ���뵱ǰĿ¼�µ�python�ű��������԰ѽű����ڹ���Ŀ¼��
		����Debug��Release���á�Ҳ�����޸�python�ű�
		(��Ȼ��Ҳ����дΪ���Ե�ַ)

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('F:/Code/VS2017/pyc/pyc')");
	*/
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	// ����ģ�飬���Լ�д��python�ű�
	pModuleName = PyUnicode_FromString("arith");
	pModule = PyImport_Import(pModuleName);
	// pModule = PyImport_ImportModule("Apaki");
	if (pModule == NULL)
	{
		printf("����pythonģ��ʧ��\n");
		return 0;
	}
	// ȷ�����õĺ�������
	pFun = PyObject_GetAttrString(pModule, "factorial");

	// ���ô��ݵĲ���
	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, PyLong_FromLong(n));

	// ���ú���������ȡ�÷���ֵ
	pValue = PyObject_CallObject(pFun, pArgs);

	if (pValue != Py_True)
	{
		printf("���ؽ����Ч\n");
		return 0;
	}
	// ������0����ʧ�ܣ�����1��������
	return 1;
 }


double py_square(double a)
{
	return a * a;
}