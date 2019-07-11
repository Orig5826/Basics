/******************************************
	重载运算符时 若用VC++6.0
只好用以下头文件。
	而对于VS2010就可以直接使用作用域std

*******************************************/

#include<iostream.h>
//#include<iostream>
//using namespace std;

class Add
{
private:
	int n;
public:
	Add(int i)
	{
		n=i;
	}
	int getn()
	{
		return n;
	}
	Add operator ++();		//++a
	//若不区分++的前置和后置  则只需上句就OK了。若需要区分只需要加上下面的一句
	Add operator ++(int);	//a++
};

Add Add::operator ++()
{
	++n;
	return *this;
}

Add Add::operator ++(int)
{
	n--;
	return *this;
}

int main()
{
	int i=0;
	Add ob(0);

	cout<<"ob.n = "<<ob.getn()<<endl;
	
	cout<<"++ob.n = "<<(++ob).getn()<<endl;

	cout<<"ob.n++ = "<<(ob++).getn()<<endl;

	cout<<"ob.n = "<<ob.getn()<<endl;

	cout<<i++<<endl;
	cout<<++i<<endl;
	//注意:
	//重载后的++并没有原++的作用。既先加和后加。但是却可以区分前置和后置，对其进行不同的操作
	//本例子，只为了区分前后置，并没有实际作用
	return 0;
}