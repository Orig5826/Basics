#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main() {
    double number = -1;
    double result = 0;
    
    // errno 中的全局变量
    errno = 0;
    result = sqrt(number);
    
    if(errno != 0)
    {
        printf("#error\n");
    }
    else
    {
        printf("result = %f\n", result);
    }

    if(errno == EDOM)
    {
        printf("Domain Error!\n");
    }
    
    if(errno == ERANGE)
    {
        printf("Range Error!\n");
    }
    return 0;
}
