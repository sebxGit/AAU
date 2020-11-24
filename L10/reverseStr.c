#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

void prompt(char* str){
  do{
  printf("What string do u want reversed? ");
  scanf("%s", str);
  } while (strlen(str) > 20);
}

void strreversed(char* str){
  char new_str[20];
  for (int i = 0; i < strlen(str); i++)
    new_str[i] = str[strlen(str) - 1 - i];
  for (int i = 0; i < strlen(str); i++)
    str[i] = new_str[i];
}

int main(void){
  char* str = malloc (MAX_SIZE * sizeof(char));
  prompt(str);
  printf("%s reversed is ", str);
  strreversed(str);
  printf("%s.", str);
}