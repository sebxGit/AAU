#include <stdlib.h>
#include <stdio.h>

int main(void){
    int num = 20;
    for(num; num < 25; num++){
      char str[10];
      itoa(num, str, 10);
      printf("%s\n", str);
    }
    return 0;

}