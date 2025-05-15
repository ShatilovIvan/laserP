#include "roots.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int roots(double a, double b, double c, double eps, double *x1, double *x2)
{

    if (fabs(a) < eps)
    {
        return NOT_A_QUADRATIC;
    }

    b = b / a;
    c = c / a;

    double d = b * b - 4 * c;

    if (fabs(d) < -eps)
    {
        return NO_ROOTS;
    }

    double *x1, *x2;
    *x1 = (-b + sqrt(d)) / 2;
    *x2 = c / *x1;

    if (fabs(d) < eps)
    {
        return ONE_ROOT;
    }

    return TWO_ROOTS;
}
