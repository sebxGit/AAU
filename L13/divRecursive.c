#include <stdio.h>

int quotient(int dividend, int divisor){
  if (dividend < divisor)
    return 0;
  else
    return 1 + quotient(dividend - divisor, divisor);
  
}


int modulus(int dividend, int divisor){
  if (dividend % divisor == 0)
    return dividend % divisor;
  else
    modulus(dividend, divisor);
}


int main(void){
  
}