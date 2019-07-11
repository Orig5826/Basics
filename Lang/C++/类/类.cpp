#include<iostream>
using namespace std;

class Rectangle
{
private:
	double length,width;
public:
	Rectangle(Rectangle &Rect);				//声明 拷贝构造函数
	Rectangle(double a,double b);			//声明带两个参数的构造函数
	void area();
	~Rectangle();
};

//拷贝构造函数
Rectangle::Rectangle(Rectangle &Rect)
{
	length=Rect.length+10;
	width=Rect.width+10;
}

//构造函数
Rectangle::Rectangle(double a=1,double b=1)
{
	length=a;
	width=b;
}

//析构函数
Rectangle::~Rectangle()
{
	cout<<"您已经成功地退出了程序！"<<endl;
}

void Rectangle::area()
{
	cout<<"面积是："<<length*width<<endl;
}

int main()
{
	Rectangle rect(5,6);
	rect.area();
	cout<<endl;

	//Rectangle rect2(rect);			//此处也可以这样调用拷贝构造函数Rectangle rect2=rect;
									//还有另一种方式自己以后慢慢体会吧
	//rect2.area();
	system("pause");
	return 0;
}