#include<iostream>
using namespace std;

class Student
{
private:
	int number;			//ѧ��
	char  name[100];	//����
	float grade;		//�ɼ�
	static int num;		//����
	static float sum;	//�ܷ�

public:
	void setdata(int n,char na[],float g)
	{
		number=n;
		strcpy(name,na);
		grade=g;
		num++;
		sum+=g;
	}
	static double average()
	{
		return sum/num;
	}
	void show()
	{
		cout<<"__________________________________"<<endl;
		cout<<"ѧ�ţ� "<<number<<" ������ "<<name<<" �ɼ��� "<<grade<<endl;
	}
};

//ע��һ�㣬��class��������static���������������ⶨ�岢�ҳ�ʼ��
int Student::num = 0;
float Student::sum = 0.0;

int main()
{
	Student stu;
	int i=0;
	char name[100];
	int number;
	float grade;

	while(i++<3)
	{
		cout<<"������ѧ�ţ�"<<endl;
		cin>>number;
		cout<<"���������֣�"<<endl;
		cin>>name;
		cout<<"������ɼ���"<<endl;
		cin>>grade;
		stu.setdata(number,name,grade);
		stu.show();
	}
	cout<<"ƽ����Ϊ�� "<<stu.average()<<endl;
	return 0;
}