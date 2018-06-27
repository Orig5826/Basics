//--------------------------------------
//数 -> 入队
//符 -> 压栈
//--------------------------------------
#include "common.h"
#include "Calc.h"
#include <math.h>

static stList list;
static stStack stack;

// ==================================== STACK ====================================
void InitStack()
{
	stack.top = -1;
}
unsigned char getStackTop()
{
	return stack.oper[stack.top];
}
bool push(unsigned char oper)
{
	if(stack.top >= STACK_SIZE)
	{
		return FALSE;
	}
	stack.top++;
	stack.oper[stack.top] = oper;
	return TRUE;
}
bool pop()
{
	if(stack.top < 0)
	{
		return FALSE;
	}
	stack.top--;
	return TRUE;
}
bool isEmptyStack()
{
	return stack.top == -1?TRUE:FALSE;
}
void DispStack()
{
	int i = 0;
	printf("\n------------STACK---------------\n");
	if(isEmptyStack())
	{
		printf("Stack Empty!\n");
		return;
	}
	for(i = 0; i < stack.top+1;i++)
	{
		printf("%c",stack.oper[i]);
		printf(" ");
	}
	printf("\n");
}

// ==================================== LIST ====================================
void InitList()
{
	list.tail = -1;
	list.head = 0;
}
bool EnList(unDatOpe datope,unsigned char flag)
{
	if(list.tail >= LIST_SIZE)
	{
		return FALSE;
	}
	list.tail++;
	list.flag[list.tail] = flag;
	if(flag)
	{
		list.datope[list.tail].oper = datope.oper;
	}
	else
	{
		list.datope[list.tail].num = datope.num;
	}
	return TRUE;
}
bool DeList(unDatOpe * datope)
{
	if(list.head > list.tail)
	{
		return FALSE;
	}
	if(list.flag[list.head])
	{
		datope->oper= list.datope[list.head++].oper;
	}
	else
	{
		datope->num = list.datope[list.head++].num;
	}
	return TRUE;
}
unDatOpe getHead()
{
	return list.datope[list.head];
}
unDatOpe getTail()
{
	return list.datope[list.tail];
}
int getListLen()
{
	return list.tail - list.head + 1;
}
bool isEmptyList()
{
	return list.tail < list.head?TRUE:FALSE;
}
void DispList()
{
	int i = 0;
	printf("\n------------List---------------\n");
	if(isEmptyList())
	{
		printf("List Empty!\n");
		return;
	}

	for(i = list.head; i <= list.tail;i++)
	{
		if(list.flag[i])
		{
			printf("%c",list.datope[i].oper);
		}
		else
		{
			printf("%f",list.datope[i].num);
		}
		printf(" ");
	}
	printf("\n");
}
// ==================================== getNum ====================================
unsigned char * getNum(unsigned char * pbuff,double * num)
{
	unsigned flag = 0;
	int integer = 0;
	int decimal = 0;
	int i = 0;
	unsigned char *p = pbuff;
	while(isdigit(*p) || *p == '.')
	{
		if(*p == '.')
		{
			flag = 1;
		}

		if(flag == 0)
		{
			integer++;
		}
		else
		{
			if(*p != '.')
			{
				decimal++;
			}
		}
		p++;
	}

	*num = 0.0;
	for(i = integer - 1; i >= 0;i--)
	{
		*num += (*pbuff - 0x30) * pow(10,i);
		pbuff++;
	}
	//略过小数点
	if(flag)
	{
		pbuff++;
	}

	if(decimal != 0)
	{
		for(i = 1; i <= decimal;i++)
		{
			*num += (*pbuff - 0x30) * pow(10,0 - i);
			pbuff++;
		}
	}
	return pbuff;
}

void CalcInit()
{
	clearBuff();
	
	InitList();
	InitStack();
}

// ==================================== Calc ====================================
static stOper s_oper[] = 
{
	{'+',1},
	{'-',1},
	{'*',2},
	{'/',2},
	{'^',3},
};
int CmpPriority(unsigned char op0,unsigned char op)
{
	int prior0 = 0,prior = 0;
	int i = 0;
	for(i = 0; i< sizeof(s_oper)/sizeof(s_oper[0]);i++)
	{
		if(op0 == s_oper[i].oper)
		{
			prior0 = s_oper[i].priority;
		}
		if(op == s_oper[i].oper)
		{
			prior = s_oper[i].priority;
		}
	}
	if(prior > prior0)
	{
		return 1;
	}
	else if(prior < prior0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


void InfixToSuffix()
{
	unsigned char *p = &g_str.buff[0];
	unDatOpe datope;
	int i = 0;
	while(i++ < getBuffLen())
	{
		if(isdigit(*p))
		{
			p = getNum(p,&datope.num);
			EnList(datope,0);
		}
		else if(*p == '=')
		{
			break;
		}
		else
		{
			if(!isEmptyStack())
			{
				//只有当当前操作符优先级大于前者时，才入栈。
				//否则，出栈，入队
				if(1 == CmpPriority(getStackTop(),*p))
				{
					push(*p);
				}
				else
				{
					//所有小于或者等于当前操作符的操作符都需要出栈
					while(1 !=  CmpPriority(getStackTop(),*p))
					{
						datope.oper = getStackTop();
						EnList(datope,1);
						pop();
					}

					//最后，剩下比当前操作符优先级小的操作符（在栈中）
					//再将此刻的操作符压入栈中
					push(*p);
				}
			}
			else
			{
				push(*p);
			}
			p++;
		}
	}

	while(!isEmptyStack())
	{
		datope.oper = getStackTop();
		EnList(datope,1);
		pop();
	}
	DispList();
	DispStack();
}

static double s_num[1024] = {0};
static int s_top = 0;
void Calculate()
{
	double result = 0.0;
	double num = 0.0;
	int i = 0;
	for(i = list.head; i <= list.tail;i++)
	{
		if(list.flag[i])
		{
			num = s_num[s_top-1];
			s_top--;
			result = s_num[s_top-1];

			switch(list.datope[i].oper)
			{
			case '+':
				{
					result += num;
				}break;
			case '-':
				{
					result -= num;
				}break;
			case '*':
				{
					result *= num;
				}break;
			case '/':
				{
					if(num == 0)
					{
						printf("divided by zero!");
					}
					else
					{
						result /= num;
					}
				}break;
			case '^':
				{
					result = pow(result,num);
				}break;
			default:
				printf("ERROR!!!");
				break;
			}
			s_num[s_top-1] = result;
		}
		else
		{
			s_num[s_top++] = list.datope[i].num;
		}
	}

	printf("result = %f\n",result);
	printf("\n----- Calc ------\n");
}