/************************************************
	fatal error C1001: INTERNAL COMPILER ERROR
����˵����VC++6.0��һ��bug
************************************************/
#include<iostream.h>
//using namespace std;

class Add
{
private:
	int n;
public:
	Add(int n=0)
	{
		Add::n=n;
	}
	int getn()
	{
		return n;
	}

	friend Add operator + (int num,Add add);
	friend Add operator + (Add add,int num);
	friend Add operator + (Add add1,Add add2);
} ;

Add operator + (int num,Add add)
{
	cout<<"________������___________"<<endl;
	add.n+=num;
	return add;
}

Add operator + (Add add,int num)
{
	cout<<"________��+��___________"<<endl;
	add.n+=num;
	return add;
}

Add operator + (Add add1,Add add2)
{
	cout<<"________�������__________"<<endl;
	add1.n+=add2.n;
	return add1;
}

int main()
{
	Add ob1(3),ob2(5),ob3;
	cout<<"ob1.n:"<<ob1.getn()<<"\t";
	cout<<"ob2.n:"<<ob2.getn()<<endl;

	ob3=4+ob1;
	cout<<"ob3=4+ob1 :"<<ob3.getn()<<endl;

	ob3=ob2+7;
	cout<<"ob3=ob2+7 :"<<ob3.getn()<<endl;

	//��+�� �����á�Add operator + (Add add1,Add add2)��
	ob3=ob1+ob2;
	cout<<"ob3=ob1+ob2 :"<<ob3.getn()<<endl;

	return 0;
}

/**********************************************
	������С�᣺
Add operator + (Add add1,Add add2)
	���ڡ������ࡢ��+����������ӡ��������������
���������͵����أ������Ͷ�Ӧ��ʽ�����
������������������ʽ������ʱ���͸��Զ�Ӧ
************************************************/