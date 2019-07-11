
#include"ListStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define ROW 10		//��
#define COL 10		//��

//���Զ����Թ��ĳ���
//#define ROW_EXIT 9
//#define COL_EXIT 4

typedef struct Move
{
	int vert;
	int hori;
}MoveSet;

MoveSet move_0[4]={{-1,0},{1,0},{0,-1},{0,1}	//0��1��2��3�ֱ�����ϡ��¡�����
};


void move_init(MoveSet Move[24][4]);
LinkStack path(LinkStack S,int ROW_EXIT,int COL_EXIT,int a[ROW+2][COL+2],MoveSet move[24][4],int num);
LinkStack optimal_solution(LinkStack S[24],int ROW_EXIT,int COL_EXIT,int a[ROW+2][COL+2],MoveSet move[24][4]);
void Show(LinkStack S,int a[ROW+2][COL+2]);

void main()
{

/****�����Թ�****/
	int a[ROW+2][COL+2]={	{1, 1,1,1,1,1,1,1,1,1,1, 1},

						{1, 0,1,0,1,0,0,0,0,0,0, 1},
						{1, 0,1,0,1,1,1,1,0,1,0, 1},
						{1, 0,1,0,0,0,0,0,0,1,0, 1},
						{1, 0,0,0,1,0,1,0,1,0,0, 1},
						{1, 0,1,0,1,0,1,0,1,0,1, 1},

						{1, 1,1,0,1,0,1,0,1,0,1, 1},
						{1, 0,0,0,1,0,1,1,1,0,0, 1},
						{1, 0,1,1,1,0,0,0,0,0,0, 1},
						{1, 0,0,0,0,1,1,1,1,1,0, 1},
						{1, 0,1,1,1,1,0,0,0,0,0, 1},

						{1, 1,1,1,1,1,1,1,1,1,1, 1},
					};

	LinkStack S;
	LinkStack _S[24];
	int ROW_EXIT,COL_EXIT;
	int num;

	MoveSet move[24][4];
	move_init(move);


/***��ʼ��·��***/
	for(num=0;num<24;num++)
	{
		InitStack(&_S[num]);
		PushStack(_S[num],1,1,0);	//�����Թ���ڼ���ʼ����
	}

	S=_S[0];
	a[S->next->i][S->next->j]=2;	//�Թ���������㼣

	while(1)
	{
			//�Թ��ĳ��ڡ����������
		srand(time(0));
		int i=rand()%ROW+1;
		int j=rand()%COL+1;
		if(a[i][j]==0)
		{
			ROW_EXIT=i;
			COL_EXIT=j;
			break;
		}
	}

/***ѡȡ����·��***/

	S=optimal_solution(_S,ROW_EXIT,COL_EXIT,a,move);
	Sleep(2000);
/***����ʾΪ�����ڡ����***/
	Show(S,a);

	getchar();
}

void move_init(MoveSet Move[24][4])
{
	int num=0,i,j,k,l;

	//��ѡ
	for(i=0;i<4;i++)
	{	//��֮
		for(j=0;j<4;j++)
		{
			if(j!=i)
			{	//Ȼ��
				for(k=0;k<4;k++)
				{
					if(k!=i && k!=j)
					{	//���
						for(l=0;l<4;l++)
						{
							if(l!=i && l!=j && l!=k)
							{
								Move[num][0]=move_0[i];
								Move[num][1]=move_0[j];
								Move[num][2]=move_0[k];
								Move[num][3]=move_0[l];
								/*
								printf("%-2d:(%d,%d) (%d,%d) (%d,%d) (%d,%d)",num,
									Move[num][0].vert,Move[num][0].hori,
									Move[num][1].vert,Move[num][1].hori,
									Move[num][2].vert,Move[num][2].hori,
									Move[num][3].vert,Move[num][3].hori);
								printf("\t%2d:%d%d%d%d\n",num,i,j,k,l);
								*/
								num++;
							}
						}
					}
				}
			}
		}
	}
}


//����߳��Թ���·��������·������ջ��
LinkStack path(LinkStack S,int ROW_EXIT,int COL_EXIT,int a[ROW+2][COL+2],MoveSet move[24][4],int num)
{
	int vert_present,hori_present,dir,vert_next,hori_next;

	while(!StackEmpty(S))		//�����ݱ�Ϊ�գ����ʾ���е�·���߹��������޳���
	{
		int success=0;

		PopStack(S,&vert_present,&hori_present,&dir);
		dir=dir+1;
		while(dir<4)				//��ѭ����Ŀ���ǡ����ߵ���·����
		{
			vert_next=vert_present+move[num][dir].vert;
			hori_next=hori_present+move[num][dir].hori;

			//�����µ�ǰλ�ô���ѡ�����ǵĶ�̬�仯
			//printf("VERT:%d HORI:%d  D=%d\n",vert_present,hori_present,dir);
			if(a[vert_next][hori_next]==0)
			{
				a[vert_next][hori_next]=2;	//�����Լ����㼣����ǰ�ȵĵط���

				if(vert_next==ROW_EXIT && hori_next==COL_EXIT)
				{
					PushStack(S,vert_present,hori_present,dir);
					PushStack(S,vert_next,hori_next,dir);
					//printf("�ɹ��߳��Թ���\n");
					success=1;
					break;					//һ�����ֳ��ڣ���û�б�Ҫ��������
				}
				else
				{
					PushStack(S,vert_present,hori_present,dir);
					vert_present=vert_next;
					hori_present=hori_next;
					dir=0;
				}
			}
			else
			{
				dir++;
			}
		}
		if(1==success)
		{
			break;
		}
		a[vert_present][hori_present]=0;
	}

	//printf("%2d:���ߵĲ�����%d\n",num,StackLength(S)-1);
	//Sleep(300);
	return S;
}

//��·����ѡȡ���Ž�
LinkStack optimal_solution(LinkStack _S[24],int ROW_EXIT,int COL_EXIT,int a[ROW+2][COL+2],MoveSet move[24][4])
{
	int num;
	int i,j,b[ROW+2][COL+2];
	LinkStack temp,r;
	for(i=0;i<ROW+2;i++)
	{
		for(j=0;j<COL+2;j++)
		{
			b[i][j]=a[i][j];
		}
	}
	path(_S[0],ROW_EXIT,COL_EXIT,b,move,0);
	temp=_S[0];
	for(num=1;num<24;num++)
	{
		for(i=0;i<ROW+2;i++)
		{
			for(j=0;j<COL+2;j++)
			{
				b[i][j]=a[i][j];
			}
		}
		
		r=path(_S[num],ROW_EXIT,COL_EXIT,b,move,num);

		if(_S[num]->next!=NULL && StackLength(temp)>StackLength(_S[num]))
		{
			DeleteStack(temp);
			temp=_S[num];
			printf("�ҵ������·�ߣ�\n");
			printf("��Ҫ��%d��\n",StackLength(temp)-1);
		}
	}
	return temp;
}

//չʾ�˶��켣
void Show(LinkStack S,int a[ROW+2][COL+2])
{
	int index=StackLength(S)-1;
	while((S=S->next)!=NULL)
	{
		int i,j;

		for(i=0;i<ROW+2;i++)
		{
			for(j=0;j<COL+2;j++)
			{
				if(a[i][j]==2)
				{
					a[i][j]=0;
				}
			}
		}

		a[S->i][S->j]=2;

		system("cls");
		for(i=0;i<ROW+2;i++)
		{
			for(j=0;j<COL+2;j++)
			{
				if(a[i][j]==1)
				{
					printf("��");
				}
				else if(a[i][j]==2)
				{
					printf("��");
					a[i][j]=0;
				}
				else
				{
					printf("  ");
				}
			}
			printf("\n");
		}

		if(index!=0)
			printf("��%d��\n",index);
		Sleep(500);
		index--;
	}
}