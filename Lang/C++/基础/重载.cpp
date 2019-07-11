/****************************************
			重载小结VC++6.0
	1.int 和 float 不能单独以同种形式共存
	2.double 和 int可共存
	3.double 和 float 共存时，只能调用double
%&@&% 1.中的单独意思是：看三
所以 暂时我这样下了结论：
	一般，用重载时，出现同形式时，就不用float了
其他情况当然可以用了，例子本程序中就有。
****************************************/
#include<iostream>
#include<stdlib.h>
using namespace std;


//此处若是把 double 改为 float 就不行了！请问：为什么？
//我试了试--似乎完全相同（除了内容）的重载函数，int 和float 不能共存

//当完全（除了内容）一样的double和float型共存时 ，运行时自动选择了double
//int 和 double 可以共存

int aver(int a,int b)
{
	cout<<"_____调用了int型_____"<<endl;
	return (a+b)/2;
}

double aver(double a,double b)
{
	cout<<"_____调用了double型_____"<<endl;
	return (a+b)/2;
}

double aver(double a,int b)						//注意：其他相同，仅仅返回值不同是不能重载的 也即此处a的值类型绝对 不能为int
{
	cout<<"_____调用了doubleXXX型_____"<<endl;
	return (a+b)/2;
}
/*
float aver(float a,float b)
{
	cout<<"_____调用了float型_____"<<endl;
	return (a+b)/2;
}
*/

float aver(float a,float b,float c)
{
	cout<<"_____不同形式调用了float型_____"<<endl;
	return (a+b+c)/3.0;
}


/*****
char aver(char a,char b)
{
	return a>b?a:b;
}
//此处只是为了试char型是否可以和其他类型共存，aver没有实际的意义
*****/


int main()
{
	cout<<"aver(3 , 9) = "<<aver(3,9)<<endl;

	//对于VC++6.0 函数的重载不能参数数目一致-------这是我第一次试验后得出的结论，不过由现在的“重载小结”看来，此出结论错了
	//参数数目一样也可以用模版
	cout<<"aver(2.5 , 3.3) = "<<aver(2.5 , 3.3)<<endl;
	cout<<"aver(2.5 , 3) = "<<aver(2.5 , 3)<<endl;

	cout<<"aver(2.5 , 3.5 , 3) = "<<aver(2.5 , 3.5 , 3)<<endl;
	system("pause");
	return 0;
}
