#include "calc.h"

//ȫ�ֱ��������ڴ�������������
double g_DNum[LENGTH_MAX] = {0};
char g_Op[LENGTH_MAX] = {0};

//���ص�ָ��Ϊ����������֮���λ��
char * AssicToDouble(char * charIn,double * result)
{
    char * ch = charIn;
    int a_int = 0,a_float = -1;
    int i = 0;

    //ÿ�ν���ú���ǰ�����
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
//�ж����ȼ�
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


//����  =>  ����������ĺ���
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
            //����ʽ��ĩβ������=���������
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
            //�˳�ѭ�������ؽ��
            break;
        }
        else if(*p == '(')
        {
            //��������ջ
            g_Op[ichar++] = *p;
            p++;
        }
        else if(*p == ')')
        {
            //�����ų�ջ
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
                //�ж��Ƿ�Ϊ����
                if((inum == 0 || (*(p-1)) == '('))
                {
                    p = AssicToDouble(p,&result);
                    g_DNum[inum++] = 0 - result;
                }
                else if(!isdigit(*(p-1)) && *(p-1) != ')')
                {
                    //����
                    BuffClear();
                    num  = sprintf(g_Buff,"������Ҫ������!\n");
                    SetBuffLen(num);
                    return FALSE;
                }
            }

            //�����������ȼ��ж�
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
    //������ϣ���ջ���
    BuffClear();

    // ================================================
    // ���
//     //1.0 �����ʾ
//     printf("%0.3f\n",g_DNum[0]);

    //2.0 ������ַ���,���趨�������
    num  = sprintf(g_Buff,"%0.3f",g_DNum[0]);
    SetBuffLen(num);
    return TRUE;
}
