#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORDS 9

char* func(char* tb[], char* word, char* lastChar, char* secondLastChar);

int main(void){
  const char* words[] = {"chair", "dairy", "boss", "circus", "fly", "dog", "church", "clue", "dish"};
  char** tb = malloc(WORDS * sizeof(char*));
  char* lastChar;
  char* secondLastChar;

   /* Assigns strings from static array to dynamic array*/
  for (int j = 0; j < WORDS; j++){
    tb[j] = malloc((strlen(words[j]) + 5) * sizeof(char));
    strcpy(tb[j], words[j]);
  }

  printf("Before: ");
  for (int k = 0; k < WORDS; k++)
    printf("%s ", tb[k]);
  
  printf("\n");

  for (int k = 0; k < WORDS; k++){
    printf("%s ", tb[k]);
    lastChar = *(tb + k) + strlen(tb[k]) - 1;
    secondLastChar = *(tb + k) + strlen(tb[k]) - 2;
    char* word = tb[k];
    tb[k] = func(tb, word, lastChar, secondLastChar);
    printf("\n");
  }
  
  printf("After: ");
  for (int k = 0; k < WORDS; k++)
    printf("%s ", tb[k]);
  

  free(tb);
  return 0;
}

char* func(char* tb[], char* word, char* lastChar, char* secondLastChar){
  char new_word[20];
  printf("-> ");
  if (strcmp(lastChar, "y") == 0){
    word[strlen(word)-1] = '\0';
    strcpy(new_word, "ies");
  }
  else if (strcmp(lastChar, "s") == 0 || (strcmp(secondLastChar, "c") && strcmp(lastChar, "h")) == 0 || (strcmp(secondLastChar, "s") && strcmp(lastChar, "h")) == 0){
    strcpy(new_word, "es");
  }
  else{
    strcpy(new_word, "s");
  }
  strcat(word, new_word);
  printf("%s", word);
  return word;
}