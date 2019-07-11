
#include"ListStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define ROW 10		//行
#define COL 10		//列

//可以定义迷宫的出口
//#define ROW_EXIT 9
//#define COL_EXIT 4

typedef struct Move
{
	int vert;
	int hori;
}MoveSet;

MoveSet move_0[4]={{-1,0},{1,0},{0,-1},{0,1}	//0、1、2、3分别代表上、下、左、右
};


void move_init(MoveSet Move[24][4]);
LinkStack path(LinkStack S,int ROW_EXIT,int COL_EXIT,int a[ROW+2][COL+2],MoveSet move[24][4],int num);
LinkStack optimal_solution(LinkStack S[24],int ROW_EXIT,int COL_EXIT,int a[ROW+2][COL+2],MoveSet move[24][4]);
void Show(LinkStack S,int a[ROW+2][COL+2]);

void main()
{

/****绘制迷宫****/
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


/***初始化路口***/
	for(num=0;num<24;num++)
	{
		InitStack(&_S[num]);
		PushStack(_S[num],1,1,0);	//定义迷宫入口及初始方向
	}

	S=_S[0];
	a[S->next->i][S->next->j]=2;	//迷宫入口留下足迹

	while(1)
	{
			//迷宫的出口——随机产生
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

/***选取最优路径***/

	S=optimal_solution(_S,ROW_EXIT,COL_EXIT,a,move);
	Sleep(2000);
/***此演示为：出口→入口***/
	Show(S,a);

	getchar();
}

void move_init(MoveSet Move[24][4])
{
	int num=0,i,j,k,l;

	//首选
	for(i=0;i<4;i++)
	{	//次之
		for(j=0;j<4;j++)
		{
			if(j!=i)
			{	//然后
				for(k=0;k<4;k++)
				{
					if(k!=i && k!=j)
					{	//最后
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


//求出走出迷宫的路径，并将路径推入栈中
LinkStack path(LinkStack S,int ROW_EXIT,int COL_EXIT,int a[ROW+2][COL+2],MoveSet move[24][4],int num)
{
	int vert_present,hori_present,dir,vert_next,hori_next;

	while(!StackEmpty(S))		//若数据表为空，则表示所有的路都走过，但是无出口
	{
		int success=0;

		PopStack(S,&vert_present,&hori_present,&dir);
		dir=dir+1;
		while(dir<4)				//该循环的目的是——走到无路可走
		{
			vert_next=vert_present+move[num][dir].vert;
			hori_next=hori_present+move[num][dir].hori;

			//看以下当前位置处，选择方向是的动态变化
			//printf("VERT:%d HORI:%d  D=%d\n",vert_present,hori_present,dir);
			if(a[vert_next][hori_next]==0)
			{
				a[vert_next][hori_next]=2;	//留下自己的足迹（当前踩的地方）

				if(vert_next==ROW_EXIT && hori_next==COL_EXIT)
				{
					PushStack(S,vert_present,hori_present,dir);
					PushStack(S,vert_next,hori_next,dir);
					//printf("成功走出迷宫！\n");
					success=1;
					break;					//一旦发现出口，就没有必要再乱找了
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

	//printf("%2d:需走的步数：%d\n",num,StackLength(S)-1);
	//Sleep(300);
	return S;
}

//从路径中选取最优解
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
			printf("找到最近的路线！\n");
			printf("需要走%d步\n",StackLength(temp)-1);
		}
	}
	return temp;
}

//展示运动轨迹
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
					printf("■");
				}
				else if(a[i][j]==2)
				{
					printf("♀");
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
			printf("第%d步\n",index);
		Sleep(500);
		index--;
	}
}