#include "roots.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test_1()
{
    double x1, x2;
    double a = 1, b = 0, c = -1, eps = 1e-15, eps_x = 1e-15;
    int res = roots(a, b, c, eps, &x1, &x2);

    assert(res == 2 && fabs(x1 - 1) < eps_x && fabs(x2 + 1) < eps_x);
}

void test_2()
{
    double x1, x2;
    double a = 1, b = 0, c = 0, eps = 1e-15, eps_x = 1e-15;
    int res = roots(a, b, c, eps, &x1, &x2);

    assert(res == 1 && fabs(x1) < eps_x);
}

void test_3()
{
    double x1, x2;
    double a = 1, b = 0, c = 1, eps = 1e-15, eps_x = 1e-15;
    int res = roots(a, b, c, eps, &x1, &x2);

    assert(res == -1);
}

void test_4()
{
    double x1, x2;
    double a = 1, b = 0, c = -1e-7, eps = 1e-7, eps_x = 1e-4;
    int res = roots(a, b, c, eps, &x1, &x2);
    assert(res == 2 && fabs(x1 - 3e-4) < eps_x && fabs(x2 + 3e-4) < eps_x);
}

void test_5()
{
    double x1, x2;
    double a = 1, b = -1e+10, c = -1, eps = 1e-11, eps_x = 1e-11;
    int res = roots(a, b, c, eps, &x1, &x2);

    assert(res == 2 && fabs(x1 - 1e+10) < eps_x && (x2 + 1e-10) < eps_x);
}

void test_6()
{
    double x1, x2;
    double a = 1, b = 0, c = -1e-8, eps = 1e-7, eps_x = 1e-7;
    int res = roots(a, b, c, eps, &x1, &x2);

    assert(res == 1 && fabs(x1) < eps_x);
}

void test_6()
{
    double x1, x2;
    double a = 1, b = 0, c = -1e-8, eps = 1e-7, eps_x = 1e-7;
    int res = roots(a, b, c, eps, &x1, &x2);

    assert(res == 1 && fabs(x1) < eps_x);
}

void test_7()
{
    double x1, x2;
    double a = 0, b = 0, c = 0, eps = 1e-7, eps_x = 1e-7;
    int res = roots(a, b, c, eps, &x1, &x2);
    assert(res == -1);
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

    return 0;
}