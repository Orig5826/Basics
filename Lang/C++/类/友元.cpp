/*******************************
		友元这儿的相关知识
	还有待于进一步提高
********************************/


#include<iostream>
#include<stdlib.h>
using namespace std;

class Rectangle;		//由于定义Name类中会用到友元成员 所以必须提前声明

class Name
{
	char *name;
	int number;
public:
	Name(char *n , int num)
	{
		name = new char[strlen(n)+1];
		strcpy(name,n);
		number = num;
	}

	void aaaaa(Rectangle &rect);		//这是该类的成员函数***
	~Name()
	{
		delete name;
	}
};

class Hao
{
public:
	void out(Rectangle &rect);
};

class Rectangle
{
private:
	float length,width;
public:
	Rectangle(float l=0 , float w=0)			//构造函数——对类数据成员赋初值
	{
		length=l;
		width=w;
	}
	float area()
	{
		return length*width;
	}

	friend float circ(Rectangle &rect);		//友元函数
	friend void Name::aaaaa(Rectangle &rect);		//友元成员***声明了Name中的成员aaaaa函数为该类的一个友元函数
	//该写友元类了
	friend class Hao;
};

float circ(Rectangle &rect)
{
	return 2*(rect.length+rect.width);
}

void Name::aaaaa(Rectangle &rect)
{
	cout<<"_____________________________"<<endl;
	cout<<"矩形名字："<<name<<endl<<"编号："<<number<<endl;
	cout<<"The area is : "<<rect.area()<<endl;
	cout<<"周长 : "<<circ(rect)<<endl;
}

void Hao::out(Rectangle &rect)
{
	cout<<"_____________________________"<<endl;
	cout<<"这是友元类Rectangle中的函数:"<<rect.area()<<"(面积)"<<endl;
}

int main()
{
	float length,width;
	char *n = new char[100];
	int number;
	cout<<"请输入矩形的长度 和 宽度 :"<<endl;
	cin>>length;
	cin>>width;
	Rectangle rect(length,width);

	cout<<"请输入矩形的名字:"<<endl;
	cin>>n;
	cout<<"请输入矩形的编号:"<<endl;
	cin>>number;

	Name name(n,number);
	name.aaaaa(rect);

	Hao h;
	h.out(rect);

	delete n;
	return 0;
}