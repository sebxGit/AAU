#include <stdio.h>
int n;

int sumIter(int n){
  int returnNum = 0;
  for (int i = 1; i <= n; i++){
    returnNum += i;
  }
  return returnNum;
}

int sumFormula(int n){
  return (n + 1) * n / 2;
}


int main(){
  printf("Type n\n");
  scanf("%d", &n);

  n = sumIter(n);

  printf("\n%d", n);
}
