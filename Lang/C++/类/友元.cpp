/*******************************
		��Ԫ��������֪ʶ
	���д��ڽ�һ�����
********************************/


#include<iostream>
#include<stdlib.h>
using namespace std;

class Rectangle;		//���ڶ���Name���л��õ���Ԫ��Ա ���Ա�����ǰ����

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

	void aaaaa(Rectangle &rect);		//���Ǹ���ĳ�Ա����***
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
	Rectangle(float l=0 , float w=0)			//���캯�������������ݳ�Ա����ֵ
	{
		length=l;
		width=w;
	}
	float area()
	{
		return length*width;
	}

	friend float circ(Rectangle &rect);		//��Ԫ����
	friend void Name::aaaaa(Rectangle &rect);		//��Ԫ��Ա***������Name�еĳ�Աaaaaa����Ϊ�����һ����Ԫ����
	//��д��Ԫ����
	friend class Hao;
};

float circ(Rectangle &rect)
{
	return 2*(rect.length+rect.width);
}

void Name::aaaaa(Rectangle &rect)
{
	cout<<"_____________________________"<<endl;
	cout<<"�������֣�"<<name<<endl<<"��ţ�"<<number<<endl;
	cout<<"The area is : "<<rect.area()<<endl;
	cout<<"�ܳ� : "<<circ(rect)<<endl;
}

void Hao::out(Rectangle &rect)
{
	cout<<"_____________________________"<<endl;
	cout<<"������Ԫ��Rectangle�еĺ���:"<<rect.area()<<"(���)"<<endl;
}

int main()
{
	float length,width;
	char *n = new char[100];
	int number;
	cout<<"��������εĳ��� �� ��� :"<<endl;
	cin>>length;
	cin>>width;
	Rectangle rect(length,width);

	cout<<"��������ε�����:"<<endl;
	cin>>n;
	cout<<"��������εı��:"<<endl;
	cin>>number;

	Name name(n,number);
	name.aaaaa(rect);

	Hao h;
	h.out(rect);

	delete n;
	return 0;
}