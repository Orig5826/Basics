#include<iostream>
using namespace std;


	//get()�Ĳ�ͬӦ��&&  getline(****)���÷�
int main()
{
	char str1[80],str2[80];
	cout<<"������һ���ַ� :";
	cout<<cin.get()<<endl;
	cin.get();

	cout<<"������һ���ַ��� ��";
	cin.getline(str2,80);

/*
	for(int i=0;i<80;i++)
	{
		cin.get(str1[i]);
		if(str1[i]=='\n')
		{
			str1[i]='\0';
			break;
		}
	}
	cout<<str1<<endl;

	cout<<"������һ���ַ��� ��";
	cin.get(str2,80);
*/
	cout<<str2<<endl;
	return 0;
}




/*****************************************************
		//	���һ�������ĵ�ַ�ķ���
int main()
{
	char *str = "Hello world ,C++";
	cout<<"����ַ���"<<str<<endl;

	cout<<"������ĵ�ַ :";
	cout<<static_cast<void *>(str)<<endl;

	cout<<"������ĵ�ַ :";
	cout<<(void*)str<<endl;
	return 0;
}
*****************************************************/
