/******************************************
	重载运算符时 若用VC++6.0
只好用以下头文件。
	而对于VS2010就可以直接使用作用域std

*******************************************/

#include<iostream.h>
//#include<iostream>
//using namespace std;

class Point
{
private:
	int i,j;
public:
	Point(int x=0,int y=0)
	{
		i=x;
		j=y;
	}
	int geti()
	{
		return i;
	}
	int getj()
	{
		return j;
	}

	void show()
	{
		cout<<"("<<geti()<<","<<getj()<<")";	//<<endl;
	}

//下面介绍的是两种类别的运算符重载形式

	/***运算符重载为类的成员函数***/
	Point operator + (Point p)
	{
		p.i=p.i+i;
		p.j=p.j+j;
		return p;
	}
	Point operator ++()
	{
		i++;
		j++;
		return *this;
	}
	/***运算符重载为类的友元函数**
	friend Point operator + (Point p1,Point p2);
	friend Point operator ++(Point &p1);
	*/
};

/*
Point operator + (Point p1,Point p2)
{
	Point temp;
	temp.i=p1.i+p2.i;
	temp.j=p1.j+p2.j;
	return temp;
}

Point operator ++(Point &p1)		
//若此处不用&号，则不能修改源class中的变量值。就和以前学过的指针那儿的用法道理一样。
//但是，要注意在声明此函数时，必须和此处的定义一致。。。
{
	p1.i++;
	p1.j++;
	return p1;
}
*/
int main()
{
	Point a1(5,6),a2(3,3),b;
	b=a1+a2;

	a1.show();
	cout<<"+";
	a2.show();
	cout<<"=";

	b.show();
	cout<<endl;

//	b++;				//隐式调用运算符
	b.operator ++();	//显示调用运算符------这两种方式仅仅针对“重载为类的成员函数”（道理你懂的）
	cout<<"b++ : ";
	b.show();
	cout<<endl;
	
	return 0;
}