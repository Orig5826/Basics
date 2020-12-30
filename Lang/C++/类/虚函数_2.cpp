/*
* 1. 虚函数的应用
* 2.引用，指针，直接传参的对比
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
	// 后面的注释皆为实现虚函数功能后
	// 对应的输出结果

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
