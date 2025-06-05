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

    if (d < -eps)
    {
        return NO_ROOTS;
    }

    if (fabs(d) < eps)
    {
        *x1 = -b / 2;
        return ONE_ROOT;
    }

    *x1 = (-b + sqrt(d)) / 2;
    *x2 = c / *x1;

    return TWO_ROOTS;
}
