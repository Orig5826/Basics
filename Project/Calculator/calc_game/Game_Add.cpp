
#include"struct.h"
#include"Game_Add.h"

char index[MAX][4]={"��","��","��","��","��","��","��","��","��","��"};
char operation[5][10]={"�ӷ�","����","�˷�","����","�������"};
char difficulty[4][8]={"���","��","��ͨ","����"};

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
//�Ա�
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

		//����
	printf("���������������\t");
	gets(Infor_L.name);
	printf("������������䣺\t");
	scanf("%d",&Infor_L.age);
	while(getchar()!='\n')
	{
		continue;
	}

	char num1[30],num2[30],home[30];
	menu_1();
	printf("��������Ŀ��Ż��Ӧ�Ĵ��룺\n");
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
				Infor_L.flag=0X50;		//ֱ�ӽ���Mixed Operation
			}break;
		case 6:
			{
				accessory();	//����
			}break;
		case 7:
			{
				exit(0);
			}break;
		default:
			{
				printf("________________________________________\n");
				printf("����������������Ŀ��Ż��Ӧ�Ĵ��룺\n");
				continue;
			}
			break;
		}

		//�������
		evaluate(Infor_L,L);

		if(n_calcu==6)
		{
			//�����˵�����������
			printf("________________________________________\n");
			printf("���룺home�ص����˵�\n");
		}
		else
		{
			//�����˵�����������
			printf("________________________________________\n");
			printf("���룺home�ص����˵� continue������ϰ\n");
		}

		while(gets(home))
		{
			if(Home(home)==1)		//������ҳ
			{
				menu_1();

				//��ʼ������
				n_calcu=0;
				n_diffi=0;

				//��ʼ���ṹ��Ϣ
				Infor_L.flag=0x00;

				printf("��������Ŀ��Ż��Ӧ�Ĵ��룺\n");
				break;
			}
			else if(n_calcu!=6 && Home(home)==2)		//������ϰ
			{
				evaluate(Infor_L,L);
				printf("________________________________________\n");
				printf("���룺home�ص����˵� continue������ϰ\n");
				continue;
			}
		}
	}

}


unsigned char Order_two(char *num, int Imax)
{
	unsigned char n_diffi;

	printf("���������Ѷȱ�Ż��Ӧ�Ĵ��룺\n");
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
			printf("�����������������Ѷȱ�Ż��Ӧ�Ĵ��룺\n");
			continue;
		}
	}
}