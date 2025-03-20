#include "roots.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double test_1()
{
    double x1, x2;

    double a = 1;
    double b = 0;
    double c = -1;
    double eps_x = 1e-7;
    double eps_var = 1e-7;

    double *list = find_roots(a, b, c, eps_x, eps_var);
    x1 = list[0];
    x2 = list[1];
    assert(fabs(x1 - 1) < eps_x);
    assert(fabs(x2 + 1) < eps_x);
}

double test_2()
{
    double x1;

    double a = 1;
    double b = 0;
    double c = 0;
    double eps_x = 1e-7;
    double eps_var = 1e-7;

    double *list = find_roots(a, b, c, eps_x, eps_var);
    x1 = list[0];
    assert(fabs(x1) < eps_x);

    free(list);
}

double test_3()
{
    double a = 1;
    double b = 0;
    double c = 1;
    double eps_x = 1e-7;
    double eps_var = 1e-7;

    double *res = find_roots(a, b, c, eps_x, eps_var);
    assert(res == NULL);

    free(res);
}

double test_4()
{
    double x1, x2;

    double a = 1;
    double b = 0;
    double c = -1E-7;
    double eps_x = 1e-4;
    double eps_var = 1e-7;

    double *list = find_roots(a, b, c, eps_x, eps_var);
    x1 = list[0];
    x2 = list[1];
    assert(fabs(x1 - 3E-4) < eps_x);
    assert(fabs(x2 + 3E-4) < eps_x);

    free(list);
}

double test_5()
{
    double x1, x2;

    double a = 1;
    double b = -1E+10;
    double c = -1;
    double eps_x = 1e-11;
    double eps_var = 1e-7;

    double *list = find_roots(a, b, c, eps_x, eps_var);
    x1 = list[0];
    x2 = list[1];
    assert(fabs(x1 - 1E+10) < eps_x);
    assert(fabs(x2 + 1E-10) < eps_x);

    free(list);
}

double test_6()
{
    double x1;

    double a = 1;
    double b = 0;
    double c = -1E-8;
    double eps_x = 1e-7;
    double eps_var = 1e-7;

    double *list = find_roots(a, b, c, eps_x, eps_var);
    assert(fabs(x1) < eps_x);

    free(list);
}

double test_7()
{
    double a = 0;
    double b = 0;
    double c = 0;
    double eps_x = 1e-7;
    double eps_var = 1e-7;

    double *res = find_roots(a, b, c, eps_x, eps_var);
    assert(res == NULL);

    free(res);
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    printf("success!\n");
    return 0;
}
