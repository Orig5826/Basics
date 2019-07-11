#include<iostream>
using namespace std;

class Rectangle
{
private:
	double length,width;
public:
	Rectangle(Rectangle &Rect);				//���� �������캯��
	Rectangle(double a,double b);			//���������������Ĺ��캯��
	void area();
	~Rectangle();
};

//�������캯��
Rectangle::Rectangle(Rectangle &Rect)
{
	length=Rect.length+10;
	width=Rect.width+10;
}

//���캯��
Rectangle::Rectangle(double a=1,double b=1)
{
	length=a;
	width=b;
}

//��������
Rectangle::~Rectangle()
{
	cout<<"���Ѿ��ɹ����˳��˳���"<<endl;
}

void Rectangle::area()
{
	cout<<"����ǣ�"<<length*width<<endl;
}

int main()
{
	Rectangle rect(5,6);
	rect.area();
	cout<<endl;

	//Rectangle rect2(rect);			//�˴�Ҳ�����������ÿ������캯��Rectangle rect2=rect;
									//������һ�ַ�ʽ�Լ��Ժ���������
	//rect2.area();
	system("pause");
	return 0;
}