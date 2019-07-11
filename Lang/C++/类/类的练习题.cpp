#include<iostream>
using namespace std;

class Student
{
private:
	int number;			//学号
	char  name[100];	//姓名
	float grade;		//成绩
	static int num;		//人数
	static float sum;	//总分

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
		cout<<"学号： "<<number<<" 姓名： "<<name<<" 成绩： "<<grade<<endl;
	}
};

//注意一点，在class中声明的static变量，必须在类外定义并且初始化
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
		cout<<"请输入学号："<<endl;
		cin>>number;
		cout<<"请输入名字："<<endl;
		cin>>name;
		cout<<"请输入成绩："<<endl;
		cin>>grade;
		stu.setdata(number,name,grade);
		stu.show();
	}
	cout<<"平均分为： "<<stu.average()<<endl;
	return 0;
}