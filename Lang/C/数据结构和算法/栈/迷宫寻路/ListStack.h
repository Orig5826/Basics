
//ջ����ʽ�洢�ṹ

#ifndef _JF_LISTSTACK_2_H_20131116_
#define _JF_LISTSTACK_2_H_20131116_

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct Node
{
	int i;
	int j;
	int d;
	struct Node *next;
}StackNode,*LinkStack;

/*********************************
		1.ջ�ĳ�ʼ��
*********************************/
void InitStack(LinkStack *top)
{
	//��ͷ���ָ�����һ������ռ�
	if((*top=(LinkStack)malloc(sizeof(StackNode)))==NULL)
	{
		exit(-1);
	}

	(*top)->next=NULL;			//��ͷ���ָ������Ϊ��

}

/*********************************
		2.ջ�Ƿ�յ��ж�
*********************************/
int StackEmpty(LinkStack top)
{
	if(top->next==NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*********************************
		3.��ջ����
*********************************/
int PushStack(LinkStack top,int i,int j,int d)
{
	StackNode *p;

	if((p=(StackNode *)malloc(sizeof(StackNode)))==NULL)
	{
		printf("�ڴ����ʧ�ܣ�");
		exit(-1);
	}
	p->i=i;
	p->j=j;
	p->d=d;

	p->next=top->next;
	top->next=p;
	return 1;
}

/*********************************
		4.��ջ����
*********************************/
int PopStack(LinkStack top,int *i,int *j,int *d)
{
	StackNode *p;
	p=top->next;
	if(!p)
	{
		printf("ջ�ѿգ�");
		return 0;
	}
	top->next=p->next;
	*i=p->i;
	*j=p->j;
	*d=p->d;

	free(p);
	return 1;
}


////�����ǳ������ϵ��⣬�Լ�����ӵ�
/*********************************
			5.ջ�ĳ���
*********************************/
int StackLength(LinkStack top)
{
	LinkStack S=top;
	int i=0;
	while((S=S->next)!=NULL)
	{
		i++;
	}
	return i;
}

/*********************************
			5.ջ�ĳ���
*********************************/
void DeleteStack(LinkStack top)
{
	LinkStack S=top;
	while((top=top->next)!=NULL)
	{
		free(S);
		S=top;
	}
}

#endif