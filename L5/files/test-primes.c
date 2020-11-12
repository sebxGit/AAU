#include "primes.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

/* Return if i is a prime number. 
   It is assumed as a precondition that the parameter i is non-negative */
int is_prime(int i){
   assert(i >= 0);

   if (i == 1) 
     return 0;
   else if (i == 2) 
     return i;
   else if (i % 2 == 0)
     return 0;
   else{
     int k, limit;
     limit = (int)(ceil(sqrt(i)));
     for (k = 3; k <= limit; k += 2)
        if (i % k == 0)
           return 0;
     return i;
   }
}

int main(){
  int m, n, c = 1;
  printf("Type n prime numbers\n");
  scanf("%d", &m);

  for (int j = 0; c <= m; j++){
    if (is_prime(j) == 0){}
    else{
      printf("Prime %d: %d\n", c, is_prime(j));
      c++;
    }
  }
  return 0;
}