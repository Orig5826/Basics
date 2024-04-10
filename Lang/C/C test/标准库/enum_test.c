#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    saturday,
    sunday, 
    monday,
    tuesday = 0,
    wednesday,
    thursday,
    friday
}workday;

int main()
{
    workday day;
    day = saturday;
    printf("%d\n", day);
    
    day = sunday;
    printf("%d\n", day);
    
    day = monday;
    printf("%d\n", day);
    
    day = tuesday;
    printf("%d\n", day);
    
    day = wednesday;
    printf("%d\n", day);
    
    day = thursday;
    printf("%d\n", day);
    
    day = friday;
    printf("%d\n", day);
    return 0;
}
