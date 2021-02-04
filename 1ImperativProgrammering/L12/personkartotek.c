#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LGT 50

typedef struct{
  char fornavn[MAX_NAME_LGT]; /* NOT FOUND IN APP*/
  char efternavn[MAX_NAME_LGT];
  char vejnavn[MAX_NAME_LGT];
  int vejnummer;
  int postnummer;
  char bynavn[MAX_NAME_LGT];
  } person;

/* Removes whitespace, commas and dots */
char* give_lastname(char* str, char* lastname, int names){
  char *token = strtok(str, " ");
  int names_sorted = 0;
  
  while(token != NULL){
    if (names == names_sorted){
      strcpy(lastname, token);
      break;
    }
    token = strtok(NULL, " ");
    names_sorted++;
  }
  return lastname;
}

int main(void){
  /*
   FILE *fp;
   char str[MAX_NAME_LGT];
   char whole_name[MAX_NAME_LGT], lastname[MAX_NAME_LGT], address[MAX_NAME_LGT], fill[MAX_NAME_LGT];
   int names;
   person p;

   // opening file for reading
   fp = fopen("adresser.text" , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return -1;
   }

  while (fgets (str, 60, fp) != NULL) {
    names = 0;
    //writing content to stdout

    sscanf(str, "%[^,] %s %[A-Z, a-z] %d %s %d %[^.]", whole_name, fill, p.vejnavn, &p.vejnummer, fill, &p.postnummer, p.bynavn);
    /* print variables out:
    printf("str: %s", str);
    printf("Variables: %s, %s %d, %d %s. ", whole_name, p.vejnavn, p.vejnummer, p.postnummer, p.bynavn);
    */
    
    int init_size = strlen(whole_name);

    for(int i = 0; i < init_size; i++){
      if (whole_name[i] == ' ')
        names++;
    }

    strcpy(p.efternavn, give_lastname(whole_name, lastname, names));

    printf("%s: %s", p.bynavn, p.efternavn);
    printf("\n");
  }

  if (feof(fp))
    printf("Reached EOF.");
  else
    printf("An error has occured.");
  fclose(fp);
  return 0;
}