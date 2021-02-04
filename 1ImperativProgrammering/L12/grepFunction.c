#include <stdio.h>
#include <string.h>

#define MAX_NAME_LGT 60
#define MAX_COMMAND 20
#define MAX_WORD 30
#define MAX_FILE 60

/* Does not use the argument command*/
int main(int argc, char *argv[]){
  char command[MAX_COMMAND], word[MAX_WORD], file[MAX_FILE];
  int i;
  // printf("\n argc = %d\n\n", argc);

  for (i = 0; i < argc; i++){
    switch(i){
      case 1: strcpy(command, argv[i]); break;
      case 2: strcpy(word, argv[i]); break;
      case 3: strcpy(file, argv[i]); break;
    }
    // printf("argv[%d] = %s\n", i, argv[i]);
  }
  // printf("cmd: %s, wrd: %s, file: %s", command, word, file);

   FILE *fp;
   char str[MAX_NAME_LGT];
   char *ret;

   // opening file for reading
   fp = fopen(file , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return -1;
   }

  while (fgets (str, 60, fp) != NULL) {
    ret = strstr(str, word);
    if (ret != NULL)
      printf("str %s", str);
  }
  return 0;
}