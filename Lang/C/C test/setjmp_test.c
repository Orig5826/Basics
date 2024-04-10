/**
    该示例模拟异常抛出的场景
*/
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf jmp_env;

double fun_div0(double data, double div)
{
    if(div == 0)
    {
        // ------------------------------
        // 即便这里填写0，实际上传的是1。但传其他值正常。
        // void longjmp(jmp_buf env, int val)
        // val == 0 ? setjmp(env) == 1 : setjmp(env) == value
        // ------------------------------
        // longjmp(jmp_env, 0); 
        // longjmp(jmp_env, -1);
        longjmp(jmp_env, 5); 
    }
    return data/div;
}

int main()
{
    double result = 0;
    int ret = 0;
    
    // 保存现场
    ret = setjmp(jmp_env);
    printf("ret = %d\n", ret);
    if(ret == 0)
    {
        // 如果 setjmp 返回 0，说明没有发生跳转
        result = fun_div0(5, 2);
        printf("1. result = %0.2f\n",result);
        
        result = fun_div0(5, 0);
        printf("2. result = %0.2f\n",result);
    }
    else
    {
        printf("#error: Dividing by zero is an illegal operation.\n");
        exit(-1);
    }

    printf("----- main exit -----\n");
    return 0;
}