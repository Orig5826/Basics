/**********************************
	在使用命名空间时，3种不同的方式，
看你使用情况而定，比如要使用大量的命
名空间里的成员，就可以采用直接声明法；
若是仅仅需要重复使用其中某几个成员，
就可以使用using指令，直接使用该命名
空间内的成员。若是仅仅用几次为数不多
的成员，那就可以使用作用域运算符了
***********************************/

#include<iostream>
#include<stdlib.h>
#include"ns.h"
using namespace std;	//3.声明法  当然，在此仅作为例子（并没有按照上述的规则）


using namespace Outer::Inter;	//2.using指令

int main()
{
	/*
	//1.使用作用域运算符 ::
	Outer::i = 0;
	Outer::f();
	cout<<Outer::i<<endl;
	*/
	i = 0;
	f();
	cout<<i<<endl;
	cout<<Outer::i<<endl;

	system("pause");
	return 0;
}
