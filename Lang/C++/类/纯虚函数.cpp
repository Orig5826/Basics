/************************************************
	声明纯虚函数的时候，需要注意：
必须声明时加上 “ = 0 ”

History:
	我忘记加了，出现了这个：
	error LNK2001: unresolved external symbol "public: virtual void __thiscall Point::set(void)" (?set@Point@@UAEXXZ)
************************************************/

#include<iostream>
using namespace std;

class Point
{
private:
	int x0,y0;
public:
	Point(int i=0,int j=0)		//定义构造函数
	{
		x0=i;
		y0=j;
	}
	virtual void set() = 0;			//声明虚函数
	virtual void show() = 0;		//声明虚函数
};	

class Line :public Point 
{
private:
	int x1,y1;
public:
	Line(int i=0, int j=0, int m=0, int n=0)	//定义构造函数
	{
		x1=m;
		y1=n;
	}
	virtual void set()
	{
		cout<<"Line 已经建立"<<endl;
	}
	virtual void show()
	{
		cout<<"line 已经绘制完毕"<<endl;
	}
};

class Ellipse :public Point 
{
private:
	int x1,y1;
public:
	Ellipse(int i=0, int j=0, int p=0, int q=0)	//定义构造函数
	{
		x1=p;
		y1=q;
	}
	virtual void set()
	{
		cout<<"Ellipse 已经建立"<<endl;
	}
	virtual void show()
	{
		cout<<"Ellipse 已经绘制完毕"<<endl;
	}
};

void setobj(Point *p)
{
	p->set();
}

void showobj(Point *p)
{
	p->show();
}

int main()
{
	Line *lineobj = new Line;
	Ellipse *ellipseobj = new Ellipse;

	setobj(lineobj);
	showobj(lineobj);
	
	setobj(ellipseobj);
	showobj(ellipseobj);
	return 0;
}