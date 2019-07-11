
//栈的链式存储结构

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
		1.栈的初始化
*********************************/
void InitStack(LinkStack *top)
{
	//给头结点指针分配一个储存空间
	if((*top=(LinkStack)malloc(sizeof(StackNode)))==NULL)
	{
		exit(-1);
	}

	(*top)->next=NULL;			//将头结点指针域置为空

}

/*********************************
		2.栈是否空的判断
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
		3.进栈操作
*********************************/
int PushStack(LinkStack top,int i,int j,int d)
{
	StackNode *p;

	if((p=(StackNode *)malloc(sizeof(StackNode)))==NULL)
	{
		printf("内存分配失败！");
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
		4.出栈操作
*********************************/
int PopStack(LinkStack top,int *i,int *j,int *d)
{
	StackNode *p;
	p=top->next;
	if(!p)
	{
		printf("栈已空！");
		return 0;
	}
	top->next=p->next;
	*i=p->i;
	*j=p->j;
	*d=p->d;

	free(p);
	return 1;
}


////以下是除了书上的外，自己乱添加的
/*********************************
			5.栈的长度
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
			5.栈的长度
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