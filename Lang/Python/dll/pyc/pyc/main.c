#include <stdio.h>
#include <Python.h>
#pragma comment(lib,"python37.lib")

#include "arith.h"

/*
	ʵ��C����Python�ű��еĺ����ӿ�
 */
void pyc_SimpleDemo(wchar_t * argv[])
{
	//Py_SetProgramName(argv[0]);
	/*
		\breaf ��ʼ��python������

		��Py_Initializeʧ�ܣ�����:ImportError:Nomodulenamedsite
		��������Ϊû�н�python��ص�·����ӵ�����������ȥ
		����Ҳ����ӻ���������ֱ�ӵ���Py_SetPythonHome��ָ��python·��Ҳ��
	*/
	Py_Initialize();

	PyRun_SimpleString("print('Hello world!')");

	for (int i = 0; i <= 100; i>=10?i+=10:i++)
	{
		printf("%4d! = ", i);
		factorial(i);
	}

	/*
		�ͷ���python��������������ڴ�
	*/
	Py_Finalize();
}

int main(int argc, wchar_t * argv[])
{
	pyc_SimpleDemo(argv);
	return 0;
}
