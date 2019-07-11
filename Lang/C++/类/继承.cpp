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
		cout<<"基类的构造函数"<<endl;
	}
	~Base()
	{
		cout<<"基类的析构函数"<<endl;
	}
	int geti()
	{
		return i;
	}
	void showi()
	{
		cout<<"基类i = "<<i<<endl;
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
		cout<<"派生类的构造函数"<<endl;
	}
	~Derived()
	{
		cout<<"派生类的析构函数"<<endl;
	}
	void showj()
	{
		//cout<<"基类i = "<<geti()<<endl;
		cout<<"基类i = "<<i<<endl;	//小结一下：***private中的数据 不能在所在类之外 进行**直接**访问——（能否间接访问得看情况）
		cout<<"派生类j = "<<j<<endl;
	}
};
int main()
{
	Derived dd(10);
	//dd.showi();
	dd.showj();
	return 0;
}