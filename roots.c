#include "roots.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double is_zero(double x, double eps)
{
    if (fabs(x) < eps)
    {
        return 0;
    }
    else
        return x;
}

double *find_roots(double a, double b, double c, double eps_x, double eps_var)
{
    double d = b * b - 4 * a * c;

    if ((is_zero(a, eps_var) == 0) || (is_zero(d, eps_var) < 0))
    {
        return NULL;
    }

    d = is_zero(d, eps_var);
    a = is_zero(a, eps_var);

    b = b / a;
    c = c / a;

    double x1, x2;
    x1 = (-b + sqrt(d)) / 2;
    x2 = c / x1;
    x1 = is_zero(x1, eps_x);
    x2 = is_zero(x2, eps_x);

    if (fabs(x1 - x2) < eps_x)
    {
        double *mas = (double *)malloc(sizeof(double));
        mas[0] = x2;
        return mas;
    }
    else
    {
        double *mas = (double *)malloc(2 * sizeof(double));
        mas[0] = x1;
        mas[1] = x2;
        return mas;
    }
}
