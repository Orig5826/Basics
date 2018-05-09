/*********************************************************************
文件：calc
时间：2017/10/12__Original__10:26:27
备注：

*********************************************************************/
#ifndef _calc_H_ 
#define _calc_H_ 
// ----------------------------------------------
// 					0.头文件
// ----------------------------------------------
#include "common.h"
#include "getBuff.h"
// ----------------------------------------------
// 					1. 常量和typedef
// ----------------------------------------------
#define LIST_SIZE	BUFF_SIZE
#define STACK_SIZE	BUFF_SIZE
// ----------------------------------------------
// 					2. 结构体 ...
// ----------------------------------------------
typedef union _unDatOpe
{
	double num;
	unsigned char oper;
}unDatOpe;

typedef struct _stList
{
	unDatOpe datope[LIST_SIZE];
	unsigned char flag[LIST_SIZE];
	int head;
	int tail;
}stList;
typedef struct _stStack
{
	unsigned char oper[STACK_SIZE];
	int top;
}stStack;
typedef struct _stOper
{
	unsigned char oper;
	int priority;
}stOper;

// ----------------------------------------------
// 					3. 函数和变量的声明
// ----------------------------------------------
unsigned char * getNum(unsigned char * pbuff,double * num);
void InfixToSuffix();
void CalcInit();
void Calculate();
/*********************************************************************
							结束
*********************************************************************/
#endif