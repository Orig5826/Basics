#include<iostream>
using namespace std;

class Rectangle
{
	private:
	double length,width;
	public:
	Rectangle();	 //声明无参数的构造函数
	Rectangle(double a,double b);	 //声明带两个参数的构造函数
	void area();
};


Rectangle::Rectangle()
{
length=1;
width=1;
}

Rectangle::Rectangle(double a ,double b = 5)
{
length=a;
width=b;
}

void Rectangle::area()
{
cout<<"面积是："<<length*width<<endl;
}

int main()
{

Rectangle rect1;
rect1.area();

Rectangle rect3(3);
rect3.area();

Rectangle rect2(5,6);
rect2.area();

system("pause");
return 0;
}

/***********************************
Rectangle::Rectangle(double a=1,double b=1)
{
    length=a;
    width=b;
}
在没有Rectangle();     //声明无参数的构造函数
的情况下，上面的语句不就是带有默认参数的构造函数吗？
为什么当两者同时出现时却不行了。


我是参考《由浅入深C++》里面的代码的，只不过书里在这段里，只有 (double a,double b=1)
我是想知道，为什么第一个参数 a不带默认参数，仅仅b带有默认参数时，和Rectangle()重载不发生问题



  我现在的理解，构造函数是给类初始化的，要么是不带参数的，要么只用带默认参数的。两个同时使用会产生编译器不知该调用哪个的错误
*/