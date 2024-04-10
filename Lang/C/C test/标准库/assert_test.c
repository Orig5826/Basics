#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

double division(double numerator, double denom)
{
    // assert
    // true: 继续执行
    // false: 打印错误信息
    assert(!(denom <= DBL_EPSILON));    // denom == 0则报错
    
    return numerator / denom;
}

int main() {
    double result = 0;
    result = division(5, 2);
    printf("result = %f\n",result);
    result = division(10, 0);
    printf("result = %f\n",result);
    return 0;
}
