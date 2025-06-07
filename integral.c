#include "integral.h"
#include <math.h>
#include <stdio.h>

double integral(double a, double b, double count_steps, double (*f)(double))
{
    double step = (b - a) / count_steps;

    double sum = 0;

    for (int i = 0; i < count_steps; i++)
    {
        sum += 0.5 * step * (f(a + step * i) + f(a + step * (i + 1)));
    }
    return sum;
}
