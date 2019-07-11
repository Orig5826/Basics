/************************************************
	fatal error C1001: INTERNAL COMPILER ERROR
网上说这是VC++6.0的一个bug
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
	cout<<"________数加类___________"<<endl;
	add.n+=num;
	return add;
}

Add operator + (Add add,int num)
{
	cout<<"________类+数___________"<<endl;
	add.n+=num;
	return add;
}

Add operator + (Add add1,Add add2)
{
	cout<<"________类类相加__________"<<endl;
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

	//类+类 必须用“Add operator + (Add add1,Add add2)”
	ob3=ob1+ob2;
	cout<<"ob3=ob1+ob2 :"<<ob3.getn()<<endl;

	return 0;
}

/**********************************************
	本程序小结：
Add operator + (Add add1,Add add2)
	对于“数加类、类+数、类类相加”三种情况都适用
而请他类型的重载，仅仅和对应形式相符。
并且若这三种重载形式都出现时，就各自对应
************************************************/