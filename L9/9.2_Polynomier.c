#include <stdio.h>
#include <stlib.h>
#include <math.h>
#define MAX_DEGREE 8

void get_polynomium(double coeff[], int* degreep);
double eval_polynomium(const double coeff[], int degree, double x);

int main(){

}

void get_polynomium(double coeff[], int* degreep){
  int total_polynomium = 0;
  for(int n = 0; n < degreep; n++){
    total_polynomium += coeff[n] * pow(x,n);
  }
  return total_polynomium;
}
