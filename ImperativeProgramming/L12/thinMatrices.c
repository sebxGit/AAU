#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILELEN 50
#define MAX_MATRIX 20

typedef struct {
  int col_ct;
  int row_ct;
  double val;
} matrix;

matrix save_data(double num, int col, int row){
  matrix result;
  result.col_ct = col;
  result.row_ct = row;
  result.val = num;
  return result;
}

void show_data(matrix m){
  printf("Num: %lf col: %d row: %d\n",
         m.val, m.col_ct, m.row_ct);
}

int main(void){
  FILE *fp;
  char *token, *ptr;
  char str[MAX_FILELEN];
  int col, row, col_ct, row_ct, index = 0;
  double num;
  matrix data_sets[MAX_MATRIX];

  
  fp = fopen("matrice.txt", "r");
  if (fp == NULL){
    perror("Error opening file");
    return -1;
  }
  fgets(str, 60, fp);
  sscanf(str, "%d %d", &col, &row);
  printf("str %s", str);

  while (fgets(str, 60, fp) != NULL) { /* Every line*/
    row_ct = 0;
    num = 0.0;
    
    token = strtok(str, " ");
    while (token != NULL){ /* Every element*/
      num = strtod(token, &ptr);
      printf("%s ", token);
      if (num != 0.0){
        data_sets[index] = save_data(num, col_ct, row_ct);
        index++;
      }
      token = strtok(NULL," "); 
      row_ct++;   
    } col_ct++;
  }
  printf("\n");
  for(int i = 0; i < index; i++)
    show_data(data_sets[i]);
  return 0;
}