 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #define ARRAY_COUNT 10

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

 int main () {
    double n[ARRAY_COUNT]; /* n is an array of 10 integers */
    time_t t;
    srand((unsigned) time(&t));

    /* initialize elements of array n to 0 */
    for (int i = 0; i < ARRAY_COUNT; i++ ) {
       n[i] = randdouble(); /* set element at location i to i + 100 */
    }

    /* output each array element's value */
    printf("Before: ");
    for (int j = 0; j < ARRAY_COUNT; j++ ) {
       printf("%.2lf  ", n[j]);
    }

    qsort(n, ARRAY_COUNT, sizeof(double), n_cmp);

    printf("\nAfter: ");
    for (int j = 0; j < ARRAY_COUNT; j++ ) {
       printf("%.2lf  ", n[j]);
    }
    return 0;
 }
