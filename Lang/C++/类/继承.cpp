#include<iostream>
using namespace std;

class Base
{
private:
	int i;
public:
	Base(int n)
	{
		i=n;
		cout<<"����Ĺ��캯��"<<endl;
	}
	~Base()
	{
		cout<<"�������������"<<endl;
	}
	int geti()
	{
		return i;
	}
	void showi()
	{
		cout<<"����i = "<<i<<endl;
	}
};

class Derived:public Base
{
private:
	int j;
	Base base;
public:
	Derived(int n):Base(n),base(n)
	{
		j=2*n;
		cout<<"������Ĺ��캯��"<<endl;
	}
	~Derived()
	{
		cout<<"���������������"<<endl;
	}
	void showj()
	{
		//cout<<"����i = "<<geti()<<endl;
		cout<<"����i = "<<i<<endl;	//С��һ�£�***private�е����� ������������֮�� ����**ֱ��**���ʡ������ܷ��ӷ��ʵÿ������
		cout<<"������j = "<<j<<endl;
	}
};
int main()
{
	Derived dd(10);
	//dd.showi();
	dd.showj();
	return 0;
}