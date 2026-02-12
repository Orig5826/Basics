
#include <stdio.h>
#include <math.h>

// 1N4148
#define IS     1e-14
#define N      1.05
#define VT     0.0258
#define RS     0.05


// // My diode constants
// #define IS     1e-12
// #define N      1.0
// #define VT     0.0258
// #define RS     0.1          // 实际
// // #define RS     1e-9      // 理想


// diode_silicon  硅基
#define DIODE_SILICON_VD_INIT    0.7
// diode_germanium 锗基
#define DIODE_GERMANIUM_VD_INIT    0.2

#define DIODE_VD_INIT    DIODE_SILICON_VD_INIT


// iteration
#define EPS         1e-9
#define MAX_ITER    20
// #define PRECISION   "%.10f"
#define PRECISION   "%.10g"


double getExpTerm(double Vd)
{
    // if(Vd > 0.8)
    // {
    //     return 0.8;
    // }
    return Vd/(N * VT);
}

double getId(double Vd)
{
    double expterm = getExpTerm(Vd);
    return IS * (exp(expterm) - 1);
}

double getIdDerivative(double Vd)
{
    double expterm = getExpTerm(Vd);
    return IS * exp(expterm) / (N * VT);
}

double getVd(double Vs)
{
    double Vd = DIODE_VD_INIT;

    double Vd_prev = 0;
    for (int i = 0; i < MAX_ITER; i++)
    {
        Vd_prev = Vd;

        double Id_D = getIdDerivative(Vd);
        double Id = getId(Vd);

        // RS + Diode模型
        // 也即：Veq = Vd + RS * Id
        // 目标：f(Vd) = Vd + RS * Id(Vd) - Vs= 0
        // f_D(Vd) = 1 + RS * Id_D
        // Iteration: 
        // Vd = Vd_prev - f(Vd)/f'(Vd)
        
        double f = Vd + RS * Id - Vs;
        double f_D = 1 + RS * Id_D;

        Vd = Vd_prev - f / f_D;

        printf("Iteration [%d]: Vd = " PRECISION " V, Id = " PRECISION " A\n", i, Vd, getId(Vd));

        if(fabs(Vd - Vd_prev) < EPS)
        {
            printf("Converged after %d iterations.\n", i);
            break;
        }

        if(i == MAX_ITER)
        {
            printf("Iteration did not converge.\n");
        }
    }
    return Vd;
}

void test()
{
    double Vs = 0.75;
    double Vd = getVd(Vs);
    double Id = getId(Vd);
    printf("----- Diode Param -----\n");
    printf("Is = " PRECISION "\n", IS);
    printf("N = " PRECISION "\n", N);
    printf("VT = " PRECISION "\n", VT);
    printf("RS = " PRECISION "\n", RS);
    
    printf("----- Vs Param -----\n");
    printf("Vs = " PRECISION "\n", Vs);

    printf("----- Diode Test -----\n");
    printf("Vd = " PRECISION "\n", Vd);
    printf("Id = " PRECISION "\n", Id);
}

int main(int argc, char *argv[])
{
    test();

    return 0;
}
