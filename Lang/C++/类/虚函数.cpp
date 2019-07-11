#include<iostream>
using namespace std;

class Animal
{
public:
	virtual void name()
	{
		cout<<"我是Animal!"<<endl;
	}
};

class Fish : public Animal
{
public:
	virtual void name()
	{
		cout<<"我是Fish!"<<endl;
	}
};

class Duck : public Animal
{
public:
	virtual void name()
	{
		cout<<"我是Duck!"<<endl;
	}
};

//注意比较一下函数的区别
void fun(Animal &aa)	// "&"表示引用
{
	aa.name();
}

void fun2(Animal aa)
{						//当没有 引用符号 时，为什么效果就像是 虚函数不起作用了??????
	aa.name();
}
////**///

int main()
{
	Fish fish;
	Animal animal;
	Duck duck;

	///对比一下的内容
	fish.name();
	animal.name();
	Animal *animal1 = &fish;		//当不设置 virtual （虚函数）时， animal1 最终指针任然指向的是 animal.name() 即相当于任然指向他的基类
	animal1->name();				//有了 virtual 时，animal1 指向的是 fish.name() 
	////----<<<<

	cout<<"________________________"<<endl;
	fun(animal);
	fun(fish);
	fun(duck);
	cout<<"________________________"<<endl;
	fun2(animal);
	fun2(fish);
	fun2(duck);
	return 0;
}