#include<iostream>
#include<stdlib.h>
using namespace std;

class Base
{
protected:
	int x;
public:
	~Base()
	{
		cout<<"³ÌÐò½áÊø ÁË°¡ °¡°¡°¡ °¡"<<endl;
	}
	Base()
	{
		x=1;
	}
};

class Base1 : virtual public Base 
{
public:
	Base1()
	{
		cout<<"Base1 x = "<<x<<endl;
	}
};

class Base2 : virtual public Base 
{
public:
	Base2()
	{
		cout<<"Base1 x = "<<x<<endl;
	}
};

class Derived : public Base1 , public Base2
{
public:
	Derived()
	{
		cout<<"Base1 x = "<<x<<endl;
	}
};

int main()
{
	Derived de;

	system("pause");
	return 0;
}