#include<iostream>
using namespace std;

class Animal
{
public:
	virtual void name()
	{
		cout<<"����Animal!"<<endl;
	}
};

class Fish : public Animal
{
public:
	virtual void name()
	{
		cout<<"����Fish!"<<endl;
	}
};

class Duck : public Animal
{
public:
	virtual void name()
	{
		cout<<"����Duck!"<<endl;
	}
};

//ע��Ƚ�һ�º���������
void fun(Animal &aa)	// "&"��ʾ����
{
	aa.name();
}

void fun2(Animal aa)
{						//��û�� ���÷��� ʱ��ΪʲôЧ�������� �麯������������??????
	aa.name();
}
////**///

int main()
{
	Fish fish;
	Animal animal;
	Duck duck;

	///�Ա�һ�µ�����
	fish.name();
	animal.name();
	Animal *animal1 = &fish;		//�������� virtual ���麯����ʱ�� animal1 ����ָ����Ȼָ����� animal.name() ���൱����Ȼָ�����Ļ���
	animal1->name();				//���� virtual ʱ��animal1 ָ����� fish.name() 
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