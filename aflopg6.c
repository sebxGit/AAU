#include <stdio.h>
#include <math.h>

double semiCircle(double x);
double trap(double a, double b, int n, double (*f)(double));

int main(void)
{
    double a = -2, b = 2;
    int n = 2;
    double area = trap(a, b, n, semiCircle);

    printf("Area: %lf\n", area);
}

double semiCircle(double x)
{
    return sqrt((4 - pow(x, 2)));
}

double trap(double a, double b, int n, double (*f)(double))
{
    double h = (b - a) / n;
    double lim = (*f)(a) + (*f)(b);
    double summation = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        summation += (*f)(i);
        printf("Function: %lf, i: %d\n", (*f)(i), i);
    }

    return h / 2 * (lim + 2 * summation);
}