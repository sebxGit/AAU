#include <stdio.h>
#include "primes.h"

int is_prime(int count, int num){
    count = 1, num = 3;
    while (count <= 100){
        int var = 0;
        for (int i = 2; i < num; i++){
            if (num % i == 0){
                var++;
            }
        }
        if (var == 0){
            printf("prime %d: %d\n", count, num);
            count++;
        }
        num++;
    }
}
