#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TABLE_COUNT 10

double randint(){
  return (int)(rand() % 50);
}

int* getTable(int count_tb){
  int* tb = (int*)malloc(count_tb * sizeof(int));
  if (tb == NULL){
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < count_tb; i++){
    tb[i] = randint();
  }
  return tb;
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

void bubble(int a[] , int n){      /* n is the size of a[] */
   int   i, j;

   for (i = 0; i < n - 1; ++i){
     for (j = n - 1; j > i; --j)
       if (a[j-1] > a[j])          /* Comparison           */
          swap(&a[j-1], &a[j]);    /* Exchange             */
   }
}

void swap(void i)

void bsort(int* tb, int count_tb, int byte_size, int(*compar)(const void *, const void *)){
  bubble(tb, (count_tb * byte_size));
}

int main(void){
  int byte_size = sizeof(int);
  time_t t;
  srand((unsigned) time(&t));

  int* tb = getTable(TABLE_COUNT);
  bsort(tb, TABLE_COUNT, byte_size, n_cmp);

  for (int i = 0; i < TABLE_COUNT; i++){
    printf("tb[%d]: %d\n3", i, tb[i]);
  }
  return 0;
}
