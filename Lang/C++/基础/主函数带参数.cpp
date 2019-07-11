
#include<iostream>
#include<iomanip>
using namespace std;

int main(int argc,char *argv[])
{
	int i;
	cout<<"当前文件的位置： "<<argv[0]<<endl;
	for(i=1;i<argc;i++)
	{
		cout<<i<<setw(2)<<".   "<<argv[i]<<endl;
	}

	//本程序为了测试一下主函数中的参数的作用和意义

	cout<<endl;
	cout<<"——输出预编译的信息——"<<endl;
	cout<<"文件名： "<<__FILE__<<endl;
	cout<<"行号： "<<__LINE__<<endl;
	cout<<"预编译日期： "<<__DATE__<<endl;
	cout<<"预编译时间： "<<__TIME__<<endl;
	system("pause");
}