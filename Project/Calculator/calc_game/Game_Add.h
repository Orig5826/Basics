
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define SIMPLEST	0x01
#define SIMPLE		0x02
#define NORMAL		0x03
#define DIFFICULTY	0x04

#define ADDITION			0x10
#define SUBTRACTION			0x20
#define MULTIPLICATION		0x30
#define DIVISION			0x40
#define MIXEDOPERATION		0x50

extern void menu_1();
extern void menu_2_1();
extern void menu_2_2();
extern int Add_calculate(Infor_List Infor_L,List *L);
extern int Sub_calculate(Infor_List Infor_L,List *L);
extern int Multi_calculate(Infor_List Infor_L,List *L);
extern int Divi_calculate(Infor_List Infor_L,List *L);
extern int Yueshu(int num);
extern unsigned char Mixed_calculate(Infor_List *Infor_L,List *L);
//extern void evaluate(Infor_List Infor_L,List L);//�����������C�ļ����ǣ�������������������һ��C�ļ��ã����Բ���ͷ�ļ��������㶮��