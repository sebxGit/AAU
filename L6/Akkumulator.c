#include <stdio.h>

#define BUFFER_SIZE 25



void scan_data(char *oper, double *value) {

  printf("gib data: ");
  scanf("%s %lf", &*oper, &*value);

}

int main(void)  {
  double value = 0.0;
  char oper[BUFFER_SIZE];

  scan_data(&oper, &value);
  printf("%s %lf", oper, value);



  return 0;
}
