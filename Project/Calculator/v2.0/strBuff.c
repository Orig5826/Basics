#include "strBuff.h"

char g_Buff[LENGTH_MAX];
int g_len = 0;


void BuffClear()
{
    int i = 0;
    for (i = 0; i < LENGTH_MAX ; i++)
    {
        g_Buff[i] = '\0';
    }
    g_len = 0;
}

int GetBuffLen()
{
    return g_len; 
}
void SetBuffLen(int len)
{
    g_len = len; 
}

// ----------------------------------------------
// 					判断输入的char是否合法
// ----------------------------------------------
BOOL islegal(char ch)
{
    if(isdigit(ch))
    {
        return TRUE;
    }
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '(':
    case ')':

    case '.':
    case '=':
        return TRUE;
        break;
    default:

        break;
    }
    return FALSE;
}

BOOL WirteBuff()
{
    char ch;
    BuffClear();
    while(ch = getchar())
    {
        if(GetBuffLen() == 0)
        {
            if(ch == '\n')
            {
                continue;
            }
        }
        else
        {
            if(ch == '\n')
            {
                break;
            }
        }
        if(isspace(ch))
        {
            continue;
        }
        //判断是否合法
        if(FALSE == islegal(ch))
        {
            BuffClear();
            return FALSE;
        }

        g_Buff[g_len] = ch;
        g_len ++;
    }
    return TRUE;
}

void ShowBuff()
{
    int i = 0;
    for (i = 0; i < GetBuffLen() ; i++)
    {
        printf("%c",g_Buff[i]);
    }
    printf("\n");
}
