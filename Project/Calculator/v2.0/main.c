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
            printf("�������ݲ��Ϸ�������������\n");
            while(getchar() != '\n');
            continue;
        }
        Calculate();
        ShowBuff();
    }
}