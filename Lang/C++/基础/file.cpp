#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<ctype.h>
using namespace std;

void f_open(char []);
int len(char[]);	//返回字符串长度
int word(char []);	//返回单词的个数
int index(char [],char []);	//返回子串首次出现的位置

int main()
{
	char str[1000];
	char a[100];
	f_open(str);
	cout<<"字符个数(含空格): "<<len(str)-1<<endl;
	cout<<"单词个数："<<word(str)<<endl;
	cout<<str<<endl;

	cout<<"请输入你要查询的单词 ："<<endl;
	cin>>a;
	if(index(str,a)==0)
	{
		cout<<"没有你要查询的单词！"<<endl;
	}
	else
	{
		cout<<"你所查询单词的首位置："<<index(str,a)<<endl;
	}
	system("pause");
	return 0;
}

void f_open(char str[])
{
	int i=0;
	ifstream fin("My test.txt");

	if(!fin)
	{
		cout<<"打开文件失败!"<<endl;
		return ;
	}
	while(fin)
	{
		fin.get(str[i++]);
	}
	str[i]='\0';
	fin.close();
}

int len(char str[])
{
	int count=0;
	while(str[count]!='\0')
	{
		count++;
	}
	return count;
}

int word(char str[])
{
	int i=0;
	int count=0;
	int flag = 1;				//计数开
	while(str[i]!='\0')
	{
		if(!isalpha(str[i]) && flag==0)
		{
			flag = 1;			//计数开
		}

		if(isalpha(str[i]) && flag==1)
		{
			count++;
			flag = 0;			//计数关
		}
		i++;
	}
	return count;
}

int index(char a[],char b[])
{
	int i;
	int j;//用来记录相同个字符个数
	int temp;
	for(i=0;i<len(a)-len(b);i++)
	{
		temp=i;
		j=0;
		while(j<=len(b) && a[temp]==b[j])
		{
			temp++;
			j++;
		}
		if(j == len(b))
			return  i;
	}
	return 0;
}