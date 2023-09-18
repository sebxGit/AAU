#include <stdio.h>
#include <math.h>

int main(void)  {
  char buffer[50];
  char op[5];
  double val = 0.0;

  printf("Operator and Value");
  fgets(buffer, 50, stdin);

  sscanf(buffer, "%s %lf", &op, &val);

  printf("Buffer: %s, Operator: %s, Value: %lf", buffer, op, val);
  return 0;
}
