#include<iostream>
#include<stdlib.h>
using namespace std;

class IntArray
{
private:
	int *a;
	int sz;
public:
	IntArray(int size)						//���幹�캯��
	{
		sz=size;
		a = new int[size];
	}
		
	//����C++�ܶ�ط��������� & ��������ú��ڸ������׶��𵽵���ʲô���ã�
	//���磬������棬û��& �ͷ��ˡ�������������
	/*********************************
			ע�⣬���緵��ֵ������������ʽ��ai.operator(2)�ķ���ֵ��һ��ʱ������������Ϊ��ֵ
	**********************************/
	int & operator[] (int i)				//�����±�
	{
		if(i<0 || i>sz)
		{
			cout<<"error"<<endl;
			exit(0);
		}
		return a[i];
	}
	
	~IntArray()								//������������
	{
		delete [] a;
	}
} ;

int main()
{
	IntArray a(5);
	a[3]=123;
	cout<<"a[3] = "<<a[3]<<endl;
	a.operator [](3) = 0;
	cout<<"a.operator [](3) = "<<a[3]<<endl;
	a[6] = 6;
	cout<<"a[6] = "<<endl;
	system("pause");
	return 0;
}