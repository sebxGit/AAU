#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORDS 9

int main(void){
  char words[9] = {"chair", "dairy", "boss", "circus", "fly", "dog", "church", "clue", "dish"};
  char *tb = (char *)malloc(WORDS * sizeof(char));
  if (tb == NULL){
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }
  for (int w = 0; w < WORDS; w++){
    tb[w] = words[w];
  }

  for (int i = 0; i < len(tb[i]); i++){
    printf("tb[%d] = %c ", i, tb[i]);
  }

}