/****************************************
			����С��VC++6.0
	1.int �� float ���ܵ�����ͬ����ʽ����
	2.double �� int�ɹ���
	3.double �� float ����ʱ��ֻ�ܵ���double
%&@&% 1.�еĵ�����˼�ǣ�����
���� ��ʱ���������˽��ۣ�
	һ�㣬������ʱ������ͬ��ʽʱ���Ͳ���float��
���������Ȼ�������ˣ����ӱ������о��С�
****************************************/
#include<iostream>
#include<stdlib.h>
using namespace std;


//�˴����ǰ� double ��Ϊ float �Ͳ����ˣ����ʣ�Ϊʲô��
//��������--�ƺ���ȫ��ͬ���������ݣ������غ�����int ��float ���ܹ���

//����ȫ���������ݣ�һ����double��float�͹���ʱ ������ʱ�Զ�ѡ����double
//int �� double ���Թ���

int aver(int a,int b)
{
	cout<<"_____������int��_____"<<endl;
	return (a+b)/2;
}

double aver(double a,double b)
{
	cout<<"_____������double��_____"<<endl;
	return (a+b)/2;
}

double aver(double a,int b)						//ע�⣺������ͬ����������ֵ��ͬ�ǲ������ص� Ҳ���˴�a��ֵ���;��� ����Ϊint
{
	cout<<"_____������doubleXXX��_____"<<endl;
	return (a+b)/2;
}
/*
float aver(float a,float b)
{
	cout<<"_____������float��_____"<<endl;
	return (a+b)/2;
}
*/

float aver(float a,float b,float c)
{
	cout<<"_____��ͬ��ʽ������float��_____"<<endl;
	return (a+b+c)/3.0;
}


/*****
char aver(char a,char b)
{
	return a>b?a:b;
}
//�˴�ֻ��Ϊ����char���Ƿ���Ժ��������͹��棬averû��ʵ�ʵ�����
*****/


int main()
{
	cout<<"aver(3 , 9) = "<<aver(3,9)<<endl;

	//����VC++6.0 ���������ز��ܲ�����Ŀһ��-------�����ҵ�һ�������ó��Ľ��ۣ����������ڵġ�����С�ᡱ�������˳����۴���
	//������Ŀһ��Ҳ������ģ��
	cout<<"aver(2.5 , 3.3) = "<<aver(2.5 , 3.3)<<endl;
	cout<<"aver(2.5 , 3) = "<<aver(2.5 , 3)<<endl;

	cout<<"aver(2.5 , 3.5 , 3) = "<<aver(2.5 , 3.5 , 3)<<endl;
	system("pause");
	return 0;
}
