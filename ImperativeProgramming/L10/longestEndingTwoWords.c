#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 20

int min(int num1, int num2){
  return (num1 < num2) ? num1 : num2;
}

void prompt(char* word1, char* word2){
  printf("Type two words for longest suffix: ");
  scanf("%s %s", word1, word2);
}
void func(char* word1, char* word2){
  char sameEnding[20];
  int len_word1 = strlen(word1);
  int len_word2 = strlen(word2);

  int w = 0;
  for (int i = 0; i < min(len_word1, len_word2); i++){
      if (word1[len_word1 - i - 1] == word2[len_word2 - i - 1]){
        sameEnding[w] = word1[len_word1 - i - 1]; /* Notice: In reverse order.*/
        w++;
      }else
        break;
  }
  strrev(sameEnding); /* Undoing the reverse-ness */ 
  printf("Longest Suffix: %s", sameEnding);
}
int main(void){
  char* word1 = malloc(MAX_SIZE * sizeof(char));
  char* word2 = malloc(MAX_SIZE * sizeof(char));
  prompt(word1, word2);
  func(word1, word2);
}