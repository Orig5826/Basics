#include "calc.h"

//全局变量，用于存放数据了运算符
double g_DNum[LENGTH_MAX] = {0};
char g_Op[LENGTH_MAX] = {0};

//返回的指针为更新完数据之后的位置
char * AssicToDouble(char * charIn,double * result)
{
    char * ch = charIn;
    int a_int = 0,a_float = -1;
    int i = 0;

    //每次进入该函数前先清空
    *result = 0;
    while(1)
    {
        if(isdigit(*ch))
        {
            if(a_float == -1)
            {
                a_int++;
            }
            else
            {
                a_float++;
            }
        }
        else if(*ch == '.')
        {
            a_float = 0;
        }
        else
        {
            break;
        }
        ch++;
    }
    for(i = 0; i < a_int;i++)
    {
        *result += (*charIn - 0x30) * pow(10,a_int - 1 - i);
        charIn++;
    }
    if(a_float > 0)
    {
        charIn++;
        for(i = 0; i < a_float;i++)
        {
            *result += (*charIn - 0x30) * pow(10,-1 - i);
            charIn++;
        }
    }
    return charIn;
}
//判断优先级
int priority(char ch)
{
    int prior = 0;
    switch(ch)
    {
    case '+':
        {
            prior = 1;
        }break;
    case '-':
        {
            prior = 1;
        }break;
    case '*':
        {
            prior = 2;
        }break;
    case '/':
        {
            prior = 2;
        }break;
    case '^':
        {
            prior = 3;
        }break;
    case '(':
        {
            prior = 0;
        }break;
    case ')':
        {
            prior = 100;
        }break;
    default:

        break;
    }
    return prior;
}


//计算  =>  计算器程序的核心
BOOL Calculate()
{
    int num = 0;

    int inum = 0,ichar = 0;
    double result = 0;
    char * p;

    p = &g_Buff[0];
    while(*p != '\n')
    {
        if(isdigit(*p))
        {
            p = AssicToDouble(p,&result);
            g_DNum[inum++] = result;
        }
        else if(*p == '=' || *p == '\0')
        {
            //在算式的末尾无论有=都会计算结果
            while(ichar != 0)
            {
                inum--;
                ichar--;
                switch(g_Op[ichar])
                {
                case '+':
                    {
                        g_DNum[inum - 1] += g_DNum[inum];
                    }break;
                case '-':
                    {
                        g_DNum[inum - 1] -= g_DNum[inum];
                    }break;
                case '*':
                    {
                        g_DNum[inum - 1] *= g_DNum[inum];
                    }break;
                case '/':
                    {
                        g_DNum[inum - 1] /= g_DNum[inum];
                    }break;
                case '^':
                    {
                        g_DNum[inum - 1] = pow(g_DNum[inum - 1],g_DNum[inum]);
                    }break;
                default:
                    break;
                }
                g_DNum[inum] = 0;
                g_Op[ichar] = 0;
            }
            inum--;
            //退出循环，返回结果
            break;
        }
        else if(*p == '(')
        {
            //左括号入栈
            g_Op[ichar++] = *p;
            p++;
        }
        else if(*p == ')')
        {
            //右括号出栈
            g_Op[ichar] = 0;
            ichar --;
            while(g_Op[ichar] != '(')
            {
                inum--;
                switch(g_Op[ichar])
                {
                case '+':
                    {
                        g_DNum[inum - 1] += g_DNum[inum];
                    }break;
                case '-':
                    {
                        g_DNum[inum - 1] -= g_DNum[inum];
                    }break;
                case '*':
                    {
                        g_DNum[inum - 1] *= g_DNum[inum];
                    }break;
                case '/':
                    {
                        g_DNum[inum - 1] /= g_DNum[inum];
                    }break;
                case '^':
                    {
                        g_DNum[inum - 1] = pow(g_DNum[inum - 1],g_DNum[inum]);
                    }break;
                default:
                    break;
                }
                g_DNum[inum] = 0;
                g_Op[ichar] = 0;
                ichar--;
            }
            g_Op[ichar] = 0;
            p++;
        }
        else
        {
            if(*p == '-' || *p == '+')
            {
                //判断是否为负数
                if((inum == 0 || (*(p-1)) == '('))
                {
                    p = AssicToDouble(p,&result);
                    g_DNum[inum++] = 0 - result;
                }
                else if(!isdigit(*(p-1)) && *(p-1) != ')')
                {
                    //出错
                    BuffClear();
                    num  = sprintf(g_Buff,"正负数要加括号!\n");
                    SetBuffLen(num);
                    return FALSE;
                }
            }

            //非括号下优先级判断
            if(ichar != 0)
            {
                while(priority(*p) <= priority(g_Op[ichar-1]))
                {
                    inum--;
                    ichar--;

                    switch(g_Op[ichar])
                    {
                    case '+':
                        {
                            g_DNum[inum - 1] += g_DNum[inum];
                        }break;
                    case '-':
                        {
                            g_DNum[inum - 1] -= g_DNum[inum];
                        }break;
                    case '*':
                        {
                            g_DNum[inum - 1] *= g_DNum[inum];
                        }break;
                    case '/':
                        {
                            g_DNum[inum - 1] /= g_DNum[inum];
                        }break;
                    case '^':
                        {
                            g_DNum[inum - 1] = pow(g_DNum[inum - 1],g_DNum[inum]);
                        }break;

                    default:
                        break;
                    }
                    g_DNum[inum] = 0;
                    g_Op[ichar] = 0;
                }
            }
            g_Op[ichar++] = *p;
            p++;
        }
    }
    //计算完毕，清空缓存
    BuffClear();

    // ================================================
    // 输出
//     //1.0 输出显示
//     printf("%0.3f\n",g_DNum[0]);

    //2.0 输出到字符串,并设定输出长度
    num  = sprintf(g_Buff,"%0.3f",g_DNum[0]);
    SetBuffLen(num);
    return TRUE;
}
