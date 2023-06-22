#include <stdio.h>
#include <math.h>

/* a og b intervalgrænser, n er finheden og */

double f(double x){
    return sqrt(4-pow(x,2));
}

double trap(double a, double b, int n, double (*f)(double)){
    double h = (b - a) / n;
}

int main(){
    double a = -2, b = 2;
    int n = 20;
    double area = trap(a, b, n, f);
    printf("Area: %lf", area);
    return 0;
}
