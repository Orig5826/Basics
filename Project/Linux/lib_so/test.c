#include "test.h"

void test(void)
{
    int i = 0;
    for(i = 0; i < 10; i++)
    {
         printf("%02x ",i);
    }
    printf("\n");
}