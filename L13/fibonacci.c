#include <stdio.h>
#include <stdlib.h>

long old_fib(int n){
  long result;

  if(n == 0)
    result = 0;
  else if (n == 1)
    result = 1;
  else
    result = old_fib(n-1) + old_fib(n-2);

  return result;
}

long fib(int n){
  long result;
  static long remem[100];
  if (n == 0)
    result = 0;
  else if (n == 1)
    result = 1;
  else if (remem[n] != 0)
    result = remem[n];
  else{
    result = fib(n-1) + fib(n-2);
    remem[n] = result;
  }
  return result;
}

int main(void){
  long i;
  /*for(i = 0; i < 45; i++){
    printf("Old_fib(%li) = %li\n", i, old_fib(i));
  }*/

  for(i = 0; i < 45; i++){
    printf("Fib(%li) = %li\n", i, fib(i));
  }
}