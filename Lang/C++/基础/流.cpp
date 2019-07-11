#include<iostream>
using namespace std;


	//get()的不同应用&&  getline(****)的用法
int main()
{
	char str1[80],str2[80];
	cout<<"请输入一个字符 :";
	cout<<cin.get()<<endl;
	cin.get();

	cout<<"请输入一行字符串 ：";
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

	cout<<"请输入一行字符串 ：";
	cin.get(str2,80);
*/
	cout<<str2<<endl;
	return 0;
}




/*****************************************************
		//	输出一个变量的地址的方法
int main()
{
	char *str = "Hello world ,C++";
	cout<<"输出字符串"<<str<<endl;

	cout<<"输出他的地址 :";
	cout<<static_cast<void *>(str)<<endl;

	cout<<"输出他的地址 :";
	cout<<(void*)str<<endl;
	return 0;
}
*****************************************************/
