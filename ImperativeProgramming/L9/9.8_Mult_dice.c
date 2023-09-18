#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dice_roll()
{
  return (int)rand() % 6;
}

int *roll_multiple_dies(int ct)
{
  int *tb = (int *)malloc(ct * sizeof(int));
  if (tb == NULL)
  {
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < ct; i++)
  {
    tb[i] = dice_roll();
  }
  return tb;
}

void roll_multiple_dies2(int **tb2, int ct)
{
  *tb2 = malloc(ct * sizeof(int));
  if (*tb2 == NULL)
  {
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < ct; i++)
  {
    *tb2[i] = dice_roll();
  }
}

int main()
{
  time_t t;
  int ct;
  srand((unsigned)time(&t));

  printf("Type amount of die throws\n");
  scanf("%d", &ct);

  int *tb = roll_multiple_dies(ct);

  for (int k = 0; k < ct; k++)
  {
    printf("%d  ", tb[k]);
  }

  printf("\n");

  int *tb2;
  roll_multiple_dies2(&tb2, ct);
  for (int k = 0; k < ct; k++)
  {
    printf("%d  ", tb2[k]);
  }

  free(tb);
  free(tb2);
  return 0;
}
