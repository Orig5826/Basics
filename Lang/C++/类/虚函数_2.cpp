/*
* 1. �麯����Ӧ��
* 2.���ã�ָ�룬ֱ�Ӵ��εĶԱ�
*/
#include <iostream>
using namespace::std;

class base
{
public:
	virtual void print()
	// void print()
	{
		cout << "base" << endl;
	}
};

class derive: public base
{
public:
	void print()
	{
		cout << "derive" << endl;
	}
};

void print(base* b)
{
	b->print();
}

void print_1(base& b)
{
	b.print();
}

void print(base b)
{
	b.print();
}


int main()
{
	// �����ע�ͽ�Ϊʵ���麯�����ܺ�
	// ��Ӧ��������

	base b;
	b.print();		//base

	derive d;
	d.print();		//derive

	base * bd;
	bd = &d;
	bd->print();	//derive

	cout << "----------" << endl;

	print(&d);		//derive
	print(d);		//base
	print_1(d);		//derive

	return 0;
}
