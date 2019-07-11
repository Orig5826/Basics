#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

char *order_opera[7]={"ADDITION","SUBTRACTION","MULTIPLICATION","DIVISION","MIXED OPERATION","ACCESSORY","QUIT"};
char order_diffi[4][12]={"SIMPLEST","SIMPLE","NORMAL","DIFFICULTY"};

char *StrUpper(char *str);
int Order_StrRight(char *str);
int IsAllDigit(const char *str);
int Order_diffiRight(char *str, int Imax);
int Home(char *home);
/****************************************
				0.Home �����˵�
****************************************/
int Home(char *home)
{
	char home1[5]="home";
	char home2[9]="continue";
	if(strcmp(StrUpper(home),StrUpper(home2))==0)
	{
		return 2;
	}
	else if(strcmp(StrUpper(home),StrUpper(home1))==0)
	{
		return 1;
	}
	else
		return 0;
}
/****************************************
				1.�˵�
****************************************/
void menu_1()
{
	printf("****************************************\n");
	printf("\t1.�ӷ���Addition��\n");
	printf("\t2.������Subtraction��\n");
	printf("\t3.�˷���Multiplication��\n");
	printf("\t4.������Division��\n");
	printf("\t5.������㣨Mixed Operation��\n");
	printf("\t6.��¼��Accessory��\n");
	printf("\t7.�˳���Quit��\n");
	printf("****************************************\n");
}

void menu_2_1()
{
	printf("****************************************\n");
	printf("\t1.��򵥣�Simplest��\n");
	printf("\t2.�򵥣�Simple��\n");
	printf("\t3.��ͨ��Normal��\n");
	printf("\t4.���ѣ�Difficulty��\n");
	//printf("\t\t5.��ҳ��Home��");
	printf("****************************************\n");
}

void menu_2_2()
{
	printf("****************************************\n");
	printf("\t1.�򵥣�Simple��\n");
	printf("\t2.��ͨ��Normal��\n");
	printf("\t3.���ѣ�Difficulty��\n");
	//printf("\t\t5.��ҳ��Home��");
	printf("****************************************\n");
}


/****************************************
				6.����accessory
****************************************/
void accessory()
{
	int i,j;
	int count=0;
	printf("________________________________________\n");
	printf("�žų˷���\n");
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=i;j++)
		{
			printf("%d��%d=%-4d",j,i,i*j);
		}
		printf("\n");
	}
	printf("11~30��ƽ����\n");
	for(j=11;j<=30;j++)
	{
		printf("%2d��%-4d ",j,j*j);
		if(++count==5)
		{
			count=0;
			printf("\n");
		}
	}
}


/****************************************
				�Ա�
****************************************/

//�������һ��
int Order_StrRight(char *str)
{
	int i=0;
	int num=0;
	for(i=0;i<7;i++)
	{
		if(strcmp(order_opera[i],StrUpper(str))==0)
		{
			num=i+1;
		}
	}
	return num;
}
int Order_diffiRight(char *str, int Imax)
{
	int i=0;
	int num=0;
	int flag = 0 ;//���-�Ա��������Ƿ�Ϸ� 0��ʾ���Ϸ�
	for(i=0;i<4;i++)
	{
		if(strcmp(order_diffi[i],StrUpper(str))==0)
		{
			if(3==Imax)
			{
				num=i;
			}
			if(4==Imax)
			{
				num=i+1;
			}
			flag = 1;//�Ϸ�
		}
	}
	if(1 == flag)
	{
		return num;
	}
	else
	{
		if(atoi(str))
		{
			return 0;
		}
		else
		{
			return -1;//����һ����Чֵ
		}
	}
}
//ת��Ϊ��д
char *StrUpper(char *str)
{
	char *pp=str;
	while(*pp!='\0')
	{
		*pp=toupper(*pp);
		pp++;
	}
	return str;
}

//ȫ����������
int IsAllDigit(const char *str)
{
	while(*str!='\0')
	{
		if(isdigit(*str)==0)
		{
			return 0;
		}
		str++;
	}
	return 1;
}
