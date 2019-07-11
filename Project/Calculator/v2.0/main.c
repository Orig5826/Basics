#include <stdio.h>
#include "calc.h"

void main(void)
{
    while(1)
    {
        printf("----------------------------------\n");
        printf("         Calculate                \n");
        printf("----------------------------------\n");
        if(FALSE == WirteBuff())
        {
            printf("输入数据不合法，请重新输入\n");
            while(getchar() != '\n');
            continue;
        }
        Calculate();
        ShowBuff();
    }
}