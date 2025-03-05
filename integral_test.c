#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "integral.h"
#define EXP 2.7182818284590452354

double cosx(double x)
{
    return cos(x);
}

double parabola(double x)
{
    return x*x;
}

double expx(double x)
{
    return pow(EXP,x);
}

void test_cosx() {
  double a = 0;
  double b = 1;

  double res = integral(a,b,cosx);

  assert(fabs(res - 0.84147 ) < 0.00001);
}

void test_parabola() {
  double a = 0;
  double b = 1;

  double res = integral(a,b,parabola);

  assert(fabs(res - 0.33333 ) < 0.00001);
}

void test_expx() {
  double a = 0;
  double b = 1;

  double res = integral(a,b,expx);

  assert(fabs(res - 1.71828 ) < 0.00001);
}

int main()
{
    test_parabola();
    test_cosx();
    test_expx();
    return 0;
}
