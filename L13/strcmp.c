#include <stdio.h>

int strcomp(char* str1, char* str2){
  printf("str1: %s, str2: %s", str1, str2);
  if (str1 == str2)
    return 0;
  else if (str1 > str2)
    return 1;
  else
    return -1;
}

int main(void){
  int num = strcomp("Apple", "Applesi");
  printf("num: %d", num);
}