#include <stdio.h>
/*
int i, j, small, large, remainder;
 
  printf("Enter two positive integers: ");
  scanf("%d %d", &i, &j);

  small = i <= j ? i : j;
  large = i <= j ? j : i;
  
  while (small > 0){
    remainder = large % small;
    large = small;
    small = remainder;
  }

  printf("GCD of %d and %d is %d\n\n", i, j, large);
  
  return 0; 
*/

int gcd(int a, int b){
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

int subt_gcd(int a, int b){
  if (a == b)
    return a;
  else if (a > b)
    return subt_gcd(a - b, b);
  else 
    return subt_gcd(a, b - a);
}

void prompt(int *a, int *b){
  printf("Enter two positive integers: ");
  scanf("%d %d", &*a, &*b);
}

int main(void) {
  int a, b;
  prompt(&a,&b);
  printf("GCD of %d and %d is %d\n\n", a, b, subt_gcd(a,b));
  return 0;
}   