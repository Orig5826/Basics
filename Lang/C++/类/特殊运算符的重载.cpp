/******************************************
	���������ʱ ����VC++6.0
ֻ��������ͷ�ļ���
	������VS2010�Ϳ���ֱ��ʹ��������std

*******************************************/

#include<iostream.h>
//#include<iostream>
//using namespace std;

class Add
{
private:
	int n;
public:
	Add(int i)
	{
		n=i;
	}
	int getn()
	{
		return n;
	}
	Add operator ++();		//++a
	//��������++��ǰ�úͺ���  ��ֻ���Ͼ��OK�ˡ�����Ҫ����ֻ��Ҫ���������һ��
	Add operator ++(int);	//a++
};

Add Add::operator ++()
{
	++n;
	return *this;
}

Add Add::operator ++(int)
{
	n--;
	return *this;
}

int main()
{
	int i=0;
	Add ob(0);

	cout<<"ob.n = "<<ob.getn()<<endl;
	
	cout<<"++ob.n = "<<(++ob).getn()<<endl;

	cout<<"ob.n++ = "<<(ob++).getn()<<endl;

	cout<<"ob.n = "<<ob.getn()<<endl;

	cout<<i++<<endl;
	cout<<++i<<endl;
	//ע��:
	//���غ��++��û��ԭ++�����á����ȼӺͺ�ӡ�����ȴ��������ǰ�úͺ��ã�������в�ͬ�Ĳ���
	//�����ӣ�ֻΪ������ǰ���ã���û��ʵ������
	return 0;
}