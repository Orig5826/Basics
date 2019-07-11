/********************************************
	该程序可以加深对拷贝构造函数的理解，
和对等号应用的理解
*********************************************/
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class Internet
{
public:
	Internet(char *name, char *url)						//定义构造函数
	{
		Internet::name = new char[strlen(name)+1];
		Internet::url = new char[strlen(url)+1];
		if(name)
		{
			strcpy(Internet::name,name);
		}
		if(url)
		{
			strcpy(Internet::url,url);
		}
	}
	
	/*******************************
		我不懂拷贝构造函数的用法
	********************************/
	Internet(Internet &temp)							//定义拷贝构造函数
	{
		Internet::name = new char[strlen(temp.name)+1];
		Internet::url = new char[strlen(temp.url)+1];
		if(this->name)
		{
			strcpy(this->name,temp.name);
		}
		if(url)
		{
			strcpy(Internet::url,temp.url);
		}
		cout<<"调用拷贝构造函数"<<endl;
	}

	~Internet()											//定义析构函数
	{
		delete [] name;
		delete [] url;
	}

	Internet& operator = (Internet &temp)				//重载运算符 = 
	{
		delete [] name;
		delete [] url;
		this->name = new char[strlen(temp.name)+1];
		this->url = new char[strlen(temp.url)+1];
		if(this->name)
		{
			strcpy(this->name,temp.name);
		}
		if(url)
		{
			strcpy(Internet::url,temp.url);
		}
		cout<<"调用重载运算符 = "<<endl;
		return *this;
	}

public:
	char *name;
	char *url;
} ;


int main()
{
	Internet a("wen.jf","714912840@qq.com");
	Internet b = a;								//此时b为刚声明的一个新类，然后用类a来初始化，需要调用“拷贝构造函数”
	cout<<b.name<<endl<<b.url<<endl;
	
	Internet c("VC++6.0","Microsoft Visual Studio 10.0");
	b = c;										//此时b为已经初始化的类，调用赋值运算符重载函数
	cout<<b.name<<endl<<b.url<<endl;

	system("pause");
	return 0;
}