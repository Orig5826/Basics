
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char * p = NULL;

void print_set()
{
    int i = 0;
    char ch[11];

    for(i = 0; i < 10; i++)
    {
        ch[i] = '0' + i;
    }
    ch[i] = '\0';
    p = &ch[0];
}

void print_str()
{
    printf("%s",p);
}

void alloc_stack_again()
{
    int i = 0;
    char ch[8];

    for(i = 0; i < 7; i++)
    {
        ch[i] = 'A' + i;
    }
    ch[i] = '\0';
}

void main()
{
    print_set();
    alloc_stack_again();
    print_str();
    // CodeBlocks²âÊÔ½á¹û
    // 012ABCDEFG
}
