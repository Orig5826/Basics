#include<fstream.h>
#include<iostream.h>
#include<stdlib.h>
//using namespace std;

int main(int argc,char *argv[])
{
	char ch;
	if(argc != 3)
	{
		cout<<"���������д���"<<endl;
		return 1;
	}

	ifstream fin(argv[1]);
	if(fin.fail())
	{
		cout<<"���ܴ�Դ�ļ�!"<<endl;
		return 1;
	}

	ofstream fout(argv[2]);
	if(!fout)
	{
		cout<<"���ܴ�Ŀ���ļ���"<<endl;
		return 1;
	}

	while(fin)
	{
		fin.get(ch);
		fout.put(ch);
	}
	cout<<argv[0]<<endl;
	cout<<argv[1]<<endl;
	cout<<argv[2]<<endl;
	fin.close();
	fout.close();
	system("pause");
	return 0;
}