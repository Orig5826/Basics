#include<iostream>
using namespace std;

class Rectangle
{
	private:
	double length,width;
	public:
	Rectangle();	 //�����޲����Ĺ��캯��
	Rectangle(double a,double b);	 //���������������Ĺ��캯��
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
cout<<"����ǣ�"<<length*width<<endl;
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
��û��Rectangle();     //�����޲����Ĺ��캯��
������£��������䲻���Ǵ���Ĭ�ϲ����Ĺ��캯����
Ϊʲô������ͬʱ����ʱȴ�����ˡ�


���ǲο�����ǳ����C++������Ĵ���ģ�ֻ��������������ֻ�� (double a,double b=1)
������֪����Ϊʲô��һ������ a����Ĭ�ϲ���������b����Ĭ�ϲ���ʱ����Rectangle()���ز���������



  �����ڵ���⣬���캯���Ǹ����ʼ���ģ�Ҫô�ǲ��������ģ�Ҫôֻ�ô�Ĭ�ϲ����ġ�����ͬʱʹ�û������������֪�õ����ĸ��Ĵ���
*/