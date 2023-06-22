#include <stdio.h>
int quotient(int dividend, int divisor);
int modulus(int dividend, int divisor);

int main(void) {
  int a, b;
  printf("Enter dividend and divisor: ");
  scanf(" %d %d", &a, &b);

  printf("%d / %d = %d\n", a, b, quotient(a, b));
  printf("%d %% %d = %d\n", a, b, modulus(a, b));
  
  return 0;
}

/* Calculate dividend / divisor - integer division 
   Precondition: divisor != 0 and both dividend and divisors are non-negative.
*/
int quotient(int dividend, int divisor){
  if (dividend < divisor)
     return 0;
  else 
     return  1 + quotient(dividend - divisor, divisor);
}

/* Calculate dividend % divisor - integer remainder.
   Precondition: divisor != 0 and both dividend and divisors are non-negative.
 */
int modulus(int dividend, int divisor){
  if (dividend < divisor)
     return dividend;
  else 
     return modulus(dividend - divisor, divisor);
}