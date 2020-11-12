#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TABLE_COUNT 100

double randdouble(){
  return (double)(rand() % 50);
}

int n_cmp(const void *ep1, const void *ep2) {
  double *tp1 = (double*)ep1,
         *tp2 = (double*)ep2;
  if (*tp1 < *tp2)
    return -1;
  else if (*tp1 > *tp2)
    return 1;
  else
    return 0;
}

double* getTable(){
  double* tb = (double*)malloc(TABLE_COUNT * sizeof(double));
  if (tb == NULL){
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < TABLE_COUNT; i++){
    tb[i] = randdouble();
  }
  return tb;
}

int main(){
   time_t t;
   srand((unsigned) time(&t));
   double* tb = getTable();
   printf("Before: ");
   for (int j = 0; j < TABLE_COUNT; j++ ) {
      printf("%.2lf  ", tb[j]);
   }

   qsort(tb, TABLE_COUNT, sizeof(double), n_cmp);

   printf("\nAfter: ");
   for (int k = 0; k < TABLE_COUNT; k++ ) {
      printf("%.2lf  ", tb[k]);
   }
   free(tb);
}
