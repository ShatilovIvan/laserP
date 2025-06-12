#include "integral.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#define EXP 2.7182818284590452354

double cosx(double x)
{
    return cos(x);
}

double parabola(double x)
{
    return x * x;
}

double expx(double x)
{
    return pow(EXP, x);
}

void test_cosx()
{
    double a = 0;
    double b = 1;
    double count_steps = 1000;

    double res = integral(a, b, count_steps, cosx);

    assert(fabs(res - 0.84147) < 0.00001);
}

void test_parabola()
{
    double a = 0;
    double b = 1;
    double count_steps = 1000;

    double res = integral(a, b, count_steps, parabola);

    assert(fabs(res - 0.33333) < 0.00001);
}

void test_expx()
{
    double a = 0;
    double b = 1;
    double count_steps = 1000;

    double res = integral(a, b, count_steps, expx);

    assert(fabs(res - 1.71828) < 0.00001);
}

int main()
{
    test_parabola();
    test_cosx();
    test_expx();
    printf("success!\n");
    return 0;
}
