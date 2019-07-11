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
				0.Home 回主菜单
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
				1.菜单
****************************************/
void menu_1()
{
	printf("****************************************\n");
	printf("\t1.加法（Addition）\n");
	printf("\t2.减法（Subtraction）\n");
	printf("\t3.乘法（Multiplication）\n");
	printf("\t4.除法（Division）\n");
	printf("\t5.混合运算（Mixed Operation）\n");
	printf("\t6.附录（Accessory）\n");
	printf("\t7.退出（Quit）\n");
	printf("****************************************\n");
}

void menu_2_1()
{
	printf("****************************************\n");
	printf("\t1.最简单（Simplest）\n");
	printf("\t2.简单（Simple）\n");
	printf("\t3.普通（Normal）\n");
	printf("\t4.困难（Difficulty）\n");
	//printf("\t\t5.主页（Home）");
	printf("****************************************\n");
}

void menu_2_2()
{
	printf("****************************************\n");
	printf("\t1.简单（Simple）\n");
	printf("\t2.普通（Normal）\n");
	printf("\t3.困难（Difficulty）\n");
	//printf("\t\t5.主页（Home）");
	printf("****************************************\n");
}


/****************************************
				6.附表accessory
****************************************/
void accessory()
{
	int i,j;
	int count=0;
	printf("________________________________________\n");
	printf("九九乘法表：\n");
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=i;j++)
		{
			printf("%d×%d=%-4d",j,i,i*j);
		}
		printf("\n");
	}
	printf("11~30的平方表：\n");
	for(j=11;j<=30;j++)
	{
		printf("%2d→%-4d ",j,j*j);
		if(++count==5)
		{
			count=0;
			printf("\n");
		}
	}
}


/****************************************
				自编
****************************************/

//与命令符一致
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
	int flag = 0 ;//标记-以辨认输入是否合法 0表示不合法
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
			flag = 1;//合法
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
			return -1;//返回一个无效值
		}
	}
}
//转化为大写
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

//全部都是数字
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
