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
	cout<<"���ں���max�ķ���ֵ�͵�һ��������ͬ������"<<endl;

	cout<<"max(1 , 3.2)="<<max(1,3.2)<<endl;	//��û��ʲô�취����ʹ����ֵ���ͺ͵�ǰ����ֵһ�£���
	cout<<"max(1.3 , 4)="<<max(1.3,4)<<endl;

	system("pause");
	return 0;
}