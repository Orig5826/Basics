/******************************************
	���������ʱ ����VC++6.0
ֻ��������ͷ�ļ���
	������VS2010�Ϳ���ֱ��ʹ��������std

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

//������ܵ����������������������ʽ

	/***���������Ϊ��ĳ�Ա����***/
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
	/***���������Ϊ�����Ԫ����**
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
//���˴�����&�ţ������޸�Դclass�еı���ֵ���ͺ���ǰѧ����ָ���Ƕ����÷�����һ����
//���ǣ�Ҫע���������˺���ʱ������ʹ˴��Ķ���һ�¡�����
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

//	b++;				//��ʽ���������
	b.operator ++();	//��ʾ���������------�����ַ�ʽ������ԡ�����Ϊ��ĳ�Ա�������������㶮�ģ�
	cout<<"b++ : ";
	b.show();
	cout<<endl;
	
	return 0;
}