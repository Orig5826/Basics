#include<iostream>
#include<stdlib.h>
using namespace std;

class IntArray
{
private:
	int *a;
	int sz;
public:
	IntArray(int size)						//定义构造函数
	{
		sz=size;
		a = new int[size];
	}
		
	//我在C++很多地方都见到了 & ，这个引用号在各处到底都起到的是什么作用？
	//比如，这句里面，没有& 就废了。。。。。。。
	/*********************************
			注意，假如返回值不采用引用形式，ai.operator(2)的返回值是一临时变量，不能作为左值
	**********************************/
	int & operator[] (int i)				//定义下标
	{
		if(i<0 || i>sz)
		{
			cout<<"error"<<endl;
			exit(0);
		}
		return a[i];
	}
	
	~IntArray()								//定义析构函数
	{
		delete [] a;
	}
} ;

int main()
{
	IntArray a(5);
	a[3]=123;
	cout<<"a[3] = "<<a[3]<<endl;
	a.operator [](3) = 0;
	cout<<"a.operator [](3) = "<<a[3]<<endl;
	a[6] = 6;
	cout<<"a[6] = "<<endl;
	system("pause");
	return 0;
}