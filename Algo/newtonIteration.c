
#include <stdio.h>
#include <math.h>

/**
 * @brief
 * sqrt(x)=2
 *
 * so:  x^2 - 2 = 0
 */
double fun(double x)
{
    return x * x - 2;
}

double D_fun(double x)
{
    return 2 * x;
}

#define EPS         1e-9
#define MAX_ITER    20
#define PRECISION   "$%.10f"

// #define EPS 1e-50
// #define MAX_ITER 100
// #define PRECISION "$%.50f"

double calc_sqrt(double x)
{
    double x0 = x;
    for (int i = 0; i < MAX_ITER; i++)
    {
        x = x0 - fun(x) / D_fun(x0);
        if(fabs(x - x0) < EPS)
        {
            break;
        }
        x0 = x;
        printf("[%d] = " PRECISION "\n", i, x);
    }
    return x;
}

void test_sqrt()
{
    double x = 2.0;
    printf("sqrt(x) = " PRECISION "\n", calc_sqrt(x));
}

int main(int argc, char *argv[])
{
    test_sqrt();

    return 0;
}
