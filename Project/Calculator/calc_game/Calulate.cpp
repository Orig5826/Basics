
#include"struct.h"
#include"Game_Add.h"

extern char index[MAX][4];
extern char operation[5][10];
extern char difficulty[4][8];
extern int IsAllDigit(const char *str);

/****************************************
				2.1�ӷ�
****************************************/
int Add_calculate(Infor_List Infor_L,List *L)
{
	int num1,num2;
	char num[10];
	int sum;
	//�ӷ�
	switch(Infor_L.flag & 0x0F)
	{
	case SIMPLEST:
		{
			num1=rand()%10;
			num2=rand()%10;
			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	case SIMPLE:
		{
			num1=rand()%100;
			num2=rand()%100;
			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);			
		}break;
	case NORMAL:
		{
			num1=rand()%1000;
			num2=rand()%1000;
			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);			
		}break;
	case DIFFICULTY:
		{
			num1=rand()%10000;
			num2=rand()%10000;
			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	default:
		break;
	}
	return 0;
}

/****************************************
				2.2����
****************************************/
int Sub_calculate(Infor_List Infor_L,List *L)
{
	int num1,num2;
	char num[10];
	int sum;
	switch(Infor_L.flag & 0x0F)
	{
	case SIMPLEST:
		{
			do
			{
				num1=rand()%10;
				num2=rand()%10;
			}while(num1<=num2);

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	case SIMPLE:
		{
			do
			{
				num1=rand()%100;
				num2=rand()%100;
			}while(num1<=num2);
			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	case NORMAL:
		{
			do
			{
				num1=rand()%1000;
				num2=rand()%1000;
			}while(num1<=num2);
			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);			
		}break;
	case DIFFICULTY:
		{
			do
			{
				num1=rand()%10000;
				num2=rand()%10000;
			}while(num1<=num2);

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	default:
		break;
	}
	return 0;
}
/****************************************
				2.3�˷�
****************************************/
int Multi_calculate(Infor_List Infor_L,List *L)
{
	int num1,num2;
	char num[10];
	int sum;
	switch((Infor_L.flag & 0x0F)+0x01)
	{
	case SIMPLE:
		{
			if(rand()%2==0)
			{
				num1=rand()%10;
				num2=rand()%100;
			}
			else
			{
				num1=rand()%100;
				num2=rand()%10;
			}

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	case NORMAL:
		{
			if(rand()%2==0)
			{
				num1=rand()%10;
				num2=rand()%1000;
			}
			else
			{
				num1=rand()%1000;
				num2=rand()%10;
			}

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	case DIFFICULTY:
		{
			if(rand()%2==0)
			{
				num1=rand()%100;
				num2=rand()%100;
			}
			else
			{
				num1=rand()%100;
				num2=rand()%100;
			}

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);			
		}break;
	default:
		break;
	}
	return 0;
}
/****************************************
				2.4����
****************************************/
int Divi_calculate(Infor_List Infor_L,List *L)
{
	int num1,num2;
	char num[10];
	int sum;
	switch((Infor_L.flag & 0x0F)+0x01)
	{
	case SIMPLE:
		{
			do
			{
				num1=rand()%100;
				num2=Yueshu(num1);		//num2()����ֵΪ0��ʾnum1Ϊ����
			}while(num1<=10 || num2>=10 ||num2==0);

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);			
		}break;
	case NORMAL:
		{
			do
			{
				num1=rand()%1000;
				num2=Yueshu(num1);
			}while(num1<=100 || num2>=10 ||num2==0);

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);
		}break;
	case DIFFICULTY:
		{
			do
			{
				num1=rand()%10000;
				num2=Yueshu(num1);
			}while(num1<=100 || num2<=10 ||num2==0);

			printf("%s %4d��%-4d=? ",index[ListLength(*L)],num1,num2);
			while(gets(num))
			{
				if(IsAllDigit(num)==1)
				{
					sum=atoi(num);
					break;
				}
				else
				{
					printf("����������������������𰸣�������\n");
				}
			}
			ListAdd(L,num1,num2,sum);			
		}break;
	default:
		break;
	}
	return 0;
}

//��һ���������Լ��
int Yueshu(int num)
{
	int dnum=2;
	int flag=FALSE;	//Ĭ�ϱ��Ϊ����
	int total=0;	//ͳ��Լ���ĸ���
	int num_index;	//��ָ�������ֱ��
	int num_index2;

	while(dnum<num)
	{
		if(num%dnum==0)
		{
			flag=TRUE;		//����
			total++;
		}
		dnum++;
	}
	
	if(flag==TRUE)
	{
		dnum=2;
		num_index=rand()%total+1;
		num_index2=0;
		while(dnum<num)
		{
			if(num%dnum==0)
			{
				num_index2++;
				if(num_index==num_index2)
				{
					return dnum;
				}
			}
			dnum++;
		}
	}
	else
	{
		return FALSE;
	}
}

/****************************************
				2.5�������
****************************************/
unsigned char Mixed_calculate(Infor_List *Infor_L,List *L)
{
	switch((rand()%4+1)<<4)
		{
		case ADDITION:
			{
				Infor_L->flag=(Infor_L->flag & 0XF0)+rand()%4+1;
				Add_calculate(*Infor_L,L);
				return ADDITION;
			}break;
		case SUBTRACTION:
			{
				Infor_L->flag=(Infor_L->flag & 0XF0)+rand()%4+1;
				Sub_calculate(*Infor_L,L);
				return SUBTRACTION;
			}break;
		case MULTIPLICATION:
			{
				Infor_L->flag=(Infor_L->flag & 0XF0)+rand()%3+1;
				Multi_calculate(*Infor_L,L);
				return MULTIPLICATION;
			}break;
		case DIVISION:
			{
				Infor_L->flag=(Infor_L->flag & 0XF0)+rand()%3+1;
				Divi_calculate(*Infor_L,L);
				return DIVISION;
			}break;

		default:
			break;
		}
}



/****************************************
			3.����_��_����
****************************************/
void evaluate(Infor_List Infor_L,List L)
{
	int i=0;
	int W_num=0;				//��¼����ļ���ĸ���

	srand(time(0));
	while(i<MAX)
	{
		switch(Infor_L.flag & 0xF0)
		{
		case ADDITION:
			{
				Add_calculate(Infor_L,&L);
			}break;
		case SUBTRACTION:
			{
				Sub_calculate(Infor_L,&L);
			}break;
		case MULTIPLICATION:
			{
				Multi_calculate(Infor_L,&L);
			}break;
		case DIVISION:
			{
				Divi_calculate(Infor_L,&L);
			}break;
		case MIXEDOPERATION:
			{
				L.flag[i]=Mixed_calculate(&Infor_L,&L);
			}break;
		default:
			break;
		}
		i++;
	}

	switch(Infor_L.flag & 0xF0)
	{
	case ADDITION:
		{
			if(ListLength(L)!=0)
			{
				printf("________________________________________\n");
				printf("\t����:%s\t���Ѷ�:%s\n",operation[((Infor_L.flag & 0xF0)>>4)-1],difficulty[(Infor_L.flag & 0X0F)-1]);
				for(i=0;i<ListLength(L);i++)
				{
					if(L.sum_w[i]!=L.num_1[i]+L.num_2[i])
					{
						printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]+L.num_2[i]);
						W_num++;
					}
				}
				Infor_L.grade=100-W_num*100/MAX;
				printf("\n������%s\t���䣺%d\t������%d\n",Infor_L.name,Infor_L.age,Infor_L.grade);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
		}break;
	case SUBTRACTION:
		{
			if(ListLength(L)!=0)
			{
				printf("________________________________________\n");
				printf("\t����:%s\t���Ѷ�:%s\n",operation[((Infor_L.flag & 0xF0)>>4)-1],difficulty[(Infor_L.flag & 0X0F)-1]);
				for(i=0;i<ListLength(L);i++)
				{
					if(L.sum_w[i]!=L.num_1[i]-L.num_2[i])
					{
						printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]-L.num_2[i]);
						W_num++;
					}
				}
				Infor_L.grade=100-W_num*100/MAX;
				printf("\n������%s\t���䣺%d\t������%d\n",Infor_L.name,Infor_L.age,Infor_L.grade);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
		}break;
	case MULTIPLICATION:
		{
			if(ListLength(L)!=0)
			{
				printf("________________________________________\n");
				printf("\t����:%s\t���Ѷ�:%s\n",operation[((Infor_L.flag & 0xF0)>>4)-1],difficulty[Infor_L.flag & 0X0F]);
				for(i=0;i<ListLength(L);i++)
				{
					if(L.sum_w[i]!=L.num_1[i]*L.num_2[i])
					{
						printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]*L.num_2[i]);
						W_num++;
					}
				}
				Infor_L.grade=100-W_num*100/MAX;
				printf("\n������%s\t���䣺%d\t������%d\n",Infor_L.name,Infor_L.age,Infor_L.grade);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
		}break;
	case DIVISION:
		{
			if(ListLength(L)!=0)
			{
				printf("________________________________________\n");
				printf("\t����:%s\t���Ѷ�:%s\n",operation[((Infor_L.flag & 0xF0)>>4)-1],difficulty[Infor_L.flag & 0X0F]);
				for(i=0;i<ListLength(L);i++)
				{
					if(L.sum_w[i]!=L.num_1[i]/L.num_2[i])
					{
						printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]/L.num_2[i]);
						W_num++;
					}
				}
				Infor_L.grade=100-W_num*100/MAX;
				printf("\n������%s\t���䣺%d\t������%d\n",Infor_L.name,Infor_L.age,Infor_L.grade);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
		}break;
	case MIXEDOPERATION:
		{
			if(ListLength(L)!=0)
			{
				printf("________________________________________\n");
				printf("\t����:���\t���Ѷ�:���\n");
				for(i=0;i<ListLength(L);i++)
				{
					switch(L.flag[i] & 0xF0)
					{
					case ADDITION:
						{
							if(L.sum_w[i]!=L.num_1[i]+L.num_2[i])
							{
								printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]+L.num_2[i]);
								W_num++;
							}						
						}break;
					case SUBTRACTION:
						{
							if(L.sum_w[i]!=L.num_1[i]-L.num_2[i])
							{
								printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]-L.num_2[i]);
								W_num++;
							}
						}break;
					case MULTIPLICATION:
						{
							if(L.sum_w[i]!=L.num_1[i]*L.num_2[i])
							{
								printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]*L.num_2[i]);
								W_num++;
							}
						}break;
					case DIVISION:
						{
							if(L.sum_w[i]!=L.num_1[i]/L.num_2[i])
							{
								printf("%s %4d��%-4d=?\t��Ĵ𰸣�%d\t��ȷ�𰸣�%d\n",index[i],L.num_1[i],L.num_2[i],L.sum_w[i],L.num_1[i]/L.num_2[i]);
								W_num++;
							}
						}break;
					default:
						break;
					}

				}
				Infor_L.grade=100-W_num*100/MAX;
				printf("\n������%s\t���䣺%d\t������%d\n",Infor_L.name,Infor_L.age,Infor_L.grade);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
		}break;
	default:
		break;
	}
}
