#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>   /* Nødvendig for tidtagning */

#define N 8000

void LinSearch(int a[], int n, int x, int print);
void BinSearch(int a[], int n, int x, int print);

int main(void){
  int x;
  char filename[20];
  FILE *myFile;
  int array[N];
  int k;
  int runs = 1000000;
  int i;

  sprintf(filename, "List%d.txt", N);
  printf("Indtast tallet du søger efter\n");
  scanf("%d", &x);

  myFile = fopen(filename, "r");

  /* indlæs fil ind i array */
  for (k = 0; k < N; k++){
    fscanf(myFile, "%d", &array[k]);
  }
  fclose(myFile);
        
  printf("Listestørrelsen er %d\n", N);
        
  /* Start tiden */
  struct timespec startTime, endTime;
  clock_gettime(CLOCK_MONOTONIC, &startTime);
        

  for (i = 0; i < runs; i++){
    BinSearch(array, N, x, 0);
  }
        
  /* Slut tiden og print den */
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  double duration = (double)(endTime.tv_sec-startTime.tv_sec) +
      1e-9*(endTime.tv_nsec-startTime.tv_nsec);
  printf("BinSearch brugte: %.7fs\n", duration);


        
  /* Start tiden */
  clock_gettime(CLOCK_MONOTONIC, &startTime);
        
  for (i = 0; i < runs; i++){
    LinSearch(array, N, x, 0);
  }
        
  /* Slut tiden og print den */
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  duration = (double)(endTime.tv_sec-startTime.tv_sec) +
             1e-9*(endTime.tv_nsec-startTime.tv_nsec);
   printf("LinSearch brugte: %.7fs\n", duration);
        
  /* Køres en gang for at printe resultat */
  LinSearch(array, N, x, 1);
  BinSearch(array, N, x, 1);
  return 0;
}

void LinSearch(int a[], int n, int x, int print){
  int i = 0;
  while(i <= n && x != a[i]) {
    i++;
  }
  if (print == 1){
    if (x == a[i]){
      printf("%d er på position %d\n",x,i+1);
    }
    else {
      printf("%d er ikke i listen \n",x);
    }
  }

  /*
  if (i <= n) {
    return i;
  }else {
    return 0;
  }
  */
}

void BinSearch(int a[], int n, int x, int print){
  int i = 0;
  int j = n;
  
  while (i<j) {
    int m = (i+j)/2;
    if (x > a[m]) {
      i = m + 1;
    } else {
      j = m;
    }
  }

  if (print == 1){
      if (x == a[i]){
         printf("%d er på position %d\n",x,i+1);
      }
      else {
         printf("%d er ikke i listen \n",x);
      }
  }

  /*
  if (x == a[i]) {
    return i;
  }else {
    return 0;
  }
  */
}


