#include <stdio.h>
#include <math.h>

/* Sebastian Truong, struon20@student.aau.dk, Grp. A409, Software 1. semester 2020,
   Aalborg Universitet. */

double trap(double a, double b, int n, double (*f)(double));
double semiCircle(double x);

int main(void){
    double a = -2, b = 2;
    int n = 2;
    
    double area = trap(a, b, n, semiCircle);
    printf("Area: %lf\n", area);
}

double trap(double a, double b, int n, double (*f)(double)){
    /* Har delt formlen op i variabel-dele, som bliver beregnet til sidst i return. 
       Benytter funktionen for semicirklen som parameter i form af pointerfunktion.*/
    double h = (b - a) / n;
    double lim = (*f)(a) + (*f)(b);
    double summation = 0;

    for (int i = 1; i <= n - 1; i++){
        summation += (*f)(i);
        printf("Function: %lf, i: %d\n", (*f)(i), i);
    }

    return h / 2 * (lim + 2 * summation);
}

double semiCircle(double x){
    return sqrt((4 - pow(x, 2)));
}