
#include<iostream>
#include<iomanip>
using namespace std;

int main(int argc,char *argv[])
{
	int i;
	cout<<"��ǰ�ļ���λ�ã� "<<argv[0]<<endl;
	for(i=1;i<argc;i++)
	{
		cout<<i<<setw(2)<<".   "<<argv[i]<<endl;
	}

	//������Ϊ�˲���һ���������еĲ��������ú�����

	cout<<endl;
	cout<<"�������Ԥ�������Ϣ����"<<endl;
	cout<<"�ļ����� "<<__FILE__<<endl;
	cout<<"�кţ� "<<__LINE__<<endl;
	cout<<"Ԥ�������ڣ� "<<__DATE__<<endl;
	cout<<"Ԥ����ʱ�䣺 "<<__TIME__<<endl;
	system("pause");
}