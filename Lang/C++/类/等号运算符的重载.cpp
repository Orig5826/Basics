/********************************************
	�ó�����Լ���Կ������캯������⣬
�ͶԵȺ�Ӧ�õ����
*********************************************/
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class Internet
{
public:
	Internet(char *name, char *url)						//���幹�캯��
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
		�Ҳ����������캯�����÷�
	********************************/
	Internet(Internet &temp)							//���忽�����캯��
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
		cout<<"���ÿ������캯��"<<endl;
	}

	~Internet()											//������������
	{
		delete [] name;
		delete [] url;
	}

	Internet& operator = (Internet &temp)				//��������� = 
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
		cout<<"������������� = "<<endl;
		return *this;
	}

public:
	char *name;
	char *url;
} ;


int main()
{
	Internet a("wen.jf","714912840@qq.com");
	Internet b = a;								//��ʱbΪ��������һ�����࣬Ȼ������a����ʼ������Ҫ���á��������캯����
	cout<<b.name<<endl<<b.url<<endl;
	
	Internet c("VC++6.0","Microsoft Visual Studio 10.0");
	b = c;										//��ʱbΪ�Ѿ���ʼ�����࣬���ø�ֵ��������غ���
	cout<<b.name<<endl<<b.url<<endl;

	system("pause");
	return 0;
}