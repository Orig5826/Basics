#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<ctype.h>
using namespace std;

void f_open(char []);
int len(char[]);	//�����ַ�������
int word(char []);	//���ص��ʵĸ���
int index(char [],char []);	//�����Ӵ��״γ��ֵ�λ��

int main()
{
	char str[1000];
	char a[100];
	f_open(str);
	cout<<"�ַ�����(���ո�): "<<len(str)-1<<endl;
	cout<<"���ʸ�����"<<word(str)<<endl;
	cout<<str<<endl;

	cout<<"��������Ҫ��ѯ�ĵ��� ��"<<endl;
	cin>>a;
	if(index(str,a)==0)
	{
		cout<<"û����Ҫ��ѯ�ĵ��ʣ�"<<endl;
	}
	else
	{
		cout<<"������ѯ���ʵ���λ�ã�"<<index(str,a)<<endl;
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
		cout<<"���ļ�ʧ��!"<<endl;
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
	int flag = 1;				//������
	while(str[i]!='\0')
	{
		if(!isalpha(str[i]) && flag==0)
		{
			flag = 1;			//������
		}

		if(isalpha(str[i]) && flag==1)
		{
			count++;
			flag = 0;			//������
		}
		i++;
	}
	return count;
}

int index(char a[],char b[])
{
	int i;
	int j;//������¼��ͬ���ַ�����
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