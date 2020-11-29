#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LGT 50

typedef struct{
  char fornavn[MAX_NAME_LGT];
  char efternavn[MAX_NAME_LGT];
  char vejnavn[MAX_NAME_LGT];
  int vejnummer;
  int postnummer;
  char bynavn[MAX_NAME_LGT];
  } person;

char* give_lastWord(char* str, char* lastWord, int words){
  char *ptr = strtok(str, " ");
  int ct = 0;
  while(ptr != NULL){
    if (words == ct){
      strcpy(lastWord, ptr);
      break;
    }
    ptr = strtok(NULL, " ");
    ct++;
  }
  return lastWord;
}

int main(void){
   FILE *fp;
   char str[60], lastName[MAX_NAME_LGT];
   int words = 0;

   /* opening file for reading */
   fp = fopen("adresser.text" , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   }
   int z = 0;

  while (fgets (str, 60, fp) != NULL) {
      /* writing content to stdout */
      printf("Count: %d, str: %s", z, str);
      z++;
     }
  if (feof(fp))
    printf("Reached EOF.");
  else
    printf("an error has occured.");
   fclose(fp);
  
/*
  char str[MAX_NAME_LGT], lastName[MAX_NAME_LGT];
  int words = 0;
  scanf("%[^,]", str);
  printf("Echo: %s", str);

  int init_size = strlen(str);
  for (int i = 0; i < init_size; i++){
    if (str[i] == ' ' || str[i] == '\n')
      words++;
  }
  strcpy(lastName, give_lastWord(str, lastName, words));
  printf("lastname: %s", lastName);*/
}