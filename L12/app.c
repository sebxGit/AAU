#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME_LGT 60

int main(){
   FILE *fp;
   char str[MAX_NAME_LGT];
   int names;

   // opening file for reading
   fp = fopen("my-file.txt" , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return -1;
   }

  while (fgets (str, 60, fp) != NULL) {
    printf("%s", str);
  }
}