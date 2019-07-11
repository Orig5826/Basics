#include<iostream>
#include<stdlib.h>
using namespace std;

template <typename NUM_1,typename NUM_2>

NUM_1 max(NUM_1 a,NUM_2 b)
{
	return (a>b?a:b);
}

int main()
{
	cout<<"max(1,2)= "<<max(1,2)<<endl;
	cout<<"max(3.2,4.6)= "<<max(3.2,4.6)<<endl;
	cout<<"max('a','A')= "<<max('a','A')<<endl;
	cout<<"由于函数max的返回值和第一个参数相同，所以"<<endl;

	cout<<"max(1 , 3.2)="<<max(1,3.2)<<endl;	//有没有什么办法可以使返回值类型和当前返回值一致？？
	cout<<"max(1.3 , 4)="<<max(1.3,4)<<endl;

	system("pause");
	return 0;
}