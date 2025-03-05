#include <stdio.h>
#include <math.h>
#include "integral.h"

double integral(double a,double b,double (*f)(double))
{
    double step = (b - a)/1000;

    double sum = 0;

    for (int i = 0; i < 1000; i++)
    {
        sum += 0.5*step*(f(a + step*i)+f(a + step*(i+1)));
    }
    return sum;
}
