
#include"struct.h"
#include"Game_Add.h"

//链表初始化
void InitList(List *L)
{
	L->last=-1;
}

//判断是否为空
int ListEmpty(List L)
{
	if(L.last==-1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//添加内容//用于给——运算表
void ListAdd(List *L,int a,int b,int sum)
{
	L->last++;
	L->num_1[L->last]=a;
	L->num_2[L->last]=b;
	L->sum_w[L->last]=sum;
}

//链表长度
int ListLength(List L)
{
	return L.last+1;
}