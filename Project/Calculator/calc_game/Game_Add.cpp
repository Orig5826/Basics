
#include"struct.h"
#include"Game_Add.h"

char index[MAX][4]={"①","②","③","④","⑤","⑥","⑦","⑧","⑨","⑩"};
char operation[5][10]={"加法","减法","乘法","除法","混合运算"};
char difficulty[4][8]={"最简单","简单","普通","困难"};

void menu_1();
void menu_2_1();
void menu_2_2();
void accessory();
int Add_calculate(Infor_List Infor_L,List *L);
int Sub_calculate(Infor_List Infor_L,List *L);
int Multi_calculate(Infor_List Infor_L,List *L);
int Divi_calculate(Infor_List Infor_L,List *L);
int Yueshu(int num);
unsigned char Mixed_calculate(Infor_List *Infor_L,List *L);
void evaluate(Infor_List Infor_L,List L);
unsigned char Order_two(char *num, int Imax);
//自编
extern int Order_StrRight(char *str);
extern int IsAllDigit(const char *str);
extern int Order_diffiRight(char *str, int Imax);
extern int Home(char *home);
void main()
{
	unsigned char n_calcu,n_diffi;
	int i=0;
	Infor_List Infor_L;
	List L;
	InitList(&L);

		//姓名
	printf("请输入你的姓名：\t");
	gets(Infor_L.name);
	printf("请输入你的年龄：\t");
	scanf("%d",&Infor_L.age);
	while(getchar()!='\n')
	{
		continue;
	}

	char num1[30],num2[30],home[30];
	menu_1();
	printf("请输入项目编号或对应的代码：\n");
	while(gets(num1))
	{
		if(Order_StrRight(num1)!=FALSE)
		{
			n_calcu=Order_StrRight(num1);
		}
		else
		{
			if(IsAllDigit(num1)==TRUE)
			{
				n_calcu=atoi(num1);
			}
		}
		switch(n_calcu)
		{
		case 1:
			{
				menu_2_1();
				n_diffi=Order_two(num2,4);
				Infor_L.flag=(n_calcu<<4) | n_diffi;
			}break;
		case 2:
			{
				menu_2_1();
				n_diffi=Order_two(num2,4);
				Infor_L.flag=(n_calcu<<4) | n_diffi;
			}break;
		case 3:
			{
				menu_2_2();
				n_diffi=Order_two(num2,3);
				Infor_L.flag=(n_calcu<<4) | n_diffi;
			}break;
		case 4:
			{
				menu_2_2();
				n_diffi=Order_two(num2,3);
				Infor_L.flag=(n_calcu<<4) | n_diffi;
			}break;
		case 5:
			{
				Infor_L.flag=0X50;		//直接进入Mixed Operation
			}break;
		case 6:
			{
				accessory();	//附表
			}break;
		case 7:
			{
				exit(0);
			}break;
		default:
			{
				printf("________________________________________\n");
				printf("输入有误，请输入项目编号或对应的代码：\n");
				continue;
			}
			break;
		}

		//结果分析
		evaluate(Infor_L,L);

		if(n_calcu==6)
		{
			//回主菜单，重新再来
			printf("________________________________________\n");
			printf("输入：home回到主菜单\n");
		}
		else
		{
			//回主菜单，重新再来
			printf("________________________________________\n");
			printf("输入：home回到主菜单 continue继续练习\n");
		}

		while(gets(home))
		{
			if(Home(home)==1)		//返回主页
			{
				menu_1();

				//初始化变量
				n_calcu=0;
				n_diffi=0;

				//初始化结构信息
				Infor_L.flag=0x00;

				printf("请输入项目编号或对应的代码：\n");
				break;
			}
			else if(n_calcu!=6 && Home(home)==2)		//继续练习
			{
				evaluate(Infor_L,L);
				printf("________________________________________\n");
				printf("输入：home回到主菜单 continue继续练习\n");
				continue;
			}
		}
	}

}


unsigned char Order_two(char *num, int Imax)
{
	unsigned char n_diffi;

	printf("请输入困难度编号或对应的代码：\n");
	while(gets(num))
	{
		if(Order_diffiRight(num,Imax)!=FALSE)
		{
			n_diffi=Order_diffiRight(num,Imax);
		}
		else
		{
			if(IsAllDigit(num)==TRUE)
			{
				n_diffi=atoi(num);
			}
		}

		if(Imax ==4 && (n_diffi==1||n_diffi==2||n_diffi==3||n_diffi==4))
		{
			return n_diffi;
		}
		else if(Imax ==3 && (n_diffi==1||n_diffi==2||n_diffi==3))
		{
			return n_diffi;
		}
		else
		{
			printf("输入有误，请输入困难度编号或对应的代码：\n");
			continue;
		}
	}
}