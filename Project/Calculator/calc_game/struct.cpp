
#include"struct.h"
#include"Game_Add.h"

//�����ʼ��
void InitList(List *L)
{
	L->last=-1;
}

//�ж��Ƿ�Ϊ��
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

//�������//���ڸ����������
void ListAdd(List *L,int a,int b,int sum)
{
	L->last++;
	L->num_1[L->last]=a;
	L->num_2[L->last]=b;
	L->sum_w[L->last]=sum;
}

//������
int ListLength(List L)
{
	return L.last+1;
}