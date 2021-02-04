#include <stdio.h>
#include <math.h>
#include <assert.h>

int is_prime();

int main(){
    int m, n;
    do{
        printf("Type an integer greater than 6.\n");
        scanf("%d", &n);
    } while (n < 6);
    
    // j is the number registered
    for (int j = 2; j <= n; j++){
        if (is_prime(j) == 0){
            continue;
        }
        for (int k = n - j; k <= n; k++){
            if (is_prime(k) == 0){
                continue;
            }
            if (j + k == n){
                printf("%d + %d = %d\n", j, k, n);
                return 0;
            }
        }
    }
}

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