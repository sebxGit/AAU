#include <stdio.h>
#include <string.h>

#define MAX_NAME_LGT 60
#define MAX_COMMAND 20
#define MAX_WORD 30
#define MAX_FILE 60


int main(int argc, char *argv[]){
  FILE *fp;
  char str[MAX_NAME_LGT], command[MAX_COMMAND], word[MAX_WORD], file[MAX_FILE];
  int i;
  printf("\n argc = %d\n\n", argc);

  for (i = 0; i < argc; i++){
    switch(i){
      case 1: strcpy(command, argv[i]); break;
      case 2: strcpy(word, argv[i]); break;
      case 3: strcpy(file, argv[i]); break;
    }
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  printf("cmd: %s, wrd: %s, file: %s", command, word, file);

  fp = fopen(file, "r");
  if (fp == NULL){
    perror("Error opening file");
    return -1;
  }

  while (fgets(str, MAX_FILE, fp) != NULL){
    printf("\n%s", str);
  }
  if (feof(fp))
    printf("\nReached EOF.");
  else
    printf("\nAn error has occured.");
  fclose(fp);

  return 0;
}