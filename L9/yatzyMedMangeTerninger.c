#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Sebastian Truong, Grp. A409, Aalborg Universitet Software 1. semester 2020 */

/* This program plays yatzy with itself. Takes the 5 highest numbered rolled die
   and then shows all the rounds of the program.*/

int promt(){
  int dies_called = 0;

  do{
    printf("How many dies do you want to throw over 5?\n");
    scanf("%d", &dies_called);
    } while (dies_called < 5);
  return dies_called;
}

int *roll_multiple_dies(int ct)
{
  int *tb = (int *)malloc(ct * sizeof(int));
  if (tb == NULL){
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < ct; i++){
    tb[i] = 1 + ((int)rand() % 6); /* Dice Roll */
  } return tb;
}

int alike(const int tb[], const int dies_total, int *score, int i){
  int ct = 0; /* Counts of the occurences of the num. */
  for (int a = 0; a < dies_total; a++){
    if (tb[a] == i){
      *score += i;
      ct += 1;
    }
  }
  return ct;
}

int pair(const int tb[], const int dies_total, int *score){
  int prev_num = -1, pairs = 0;
  for (int i = 0; i < dies_total; i++){
    if (tb[i] == prev_num){
      // Assuming 1 pair = 0, if there are two pairs.
      pairs += 1;
      *score += tb[i] + prev_num;
      i++; // Skips next number, because it is already in pair.
      printf("%d == %d\n", tb[i], prev_num);
    } prev_num = tb[i];
  } printf("\nPairs: %d, Score: %d", pairs, *score);
return pairs;
}

int ofAKind(const int tb[], const int dies_total, int *score){
  /* Checks four of a kind first. */
  for (int i = 0; i < dies_total - 3; i++){
    if (tb[i] == tb[i + 1] && tb[i] == tb[i + 2] && tb[i] == tb[i + 3]){
      *score += tb[i] * 4;
      printf("\nFour of a kind: Num %d, Score: %d", tb[i], *score);
      return 4;
    }
  }
  /* Then proceedes with the three alike. */
  for (int i = 0; i < dies_total - 2; i++){
    if (tb[i] == tb[i + 1] && tb[i] == tb[i + 2]){
      *score += tb[i] * 3;
      printf("\nThree of a kind: Num %d, Score: %d", tb[i], *score);
      return 3;
    }
  } 
  printf("\nNone of a kind: Score: %d", *score);
  return 0;
}

int straight(const int tb[], const int dies_total, int *score){
  /* Making a new string from the original array to a string. */
  char tb_inString[6];
  for (int i = 0; i < dies_total; i++)
    tb_inString[i] = tb[i] + '0'; /* Syntax for converting an int to a char. */
  
  tb_inString[5] = '\0'; /* Strings have this null value on the last element of the array.*/
  
  if (strcmp(tb_inString, "12345") == 0){
    *score += 15;
    printf("\nSmall Straight! Score: %d", *score);
    return -1;
  }

  if (strcmp(tb_inString, "23456") == 0){
    *score += 20;
    printf("\nLarge Straight! Score: %d", *score);
    return 1;
  } 
  printf("\nNo Straights. Score: %d", *score);
  return 0;
}

int fullHouse(const int tb[], const int dies_total, int *score, int pairs, int kinds){
  if (pairs == 1 && kinds == 3){
    *score += (tb[0] == tb[2]) ? tb[0] * 3 + tb[4] * 2 : tb[0] * 2 + tb[4] * 3;
    printf("\nFull House! Score %d", *score);
    return 1;
  } 
  printf("\nNo Full House. Score: %d", *score);
  return 0;
}

int chance(const int tb[], const int dies_total, int *score){
  for (int i = 0; i < dies_total; i++)
    *score += tb[i];
  printf("\nChance! Score: %d", *score);
  return 1;
}

int yatzy(const int tb[], const int ct_array, int *score){
  /* Making a new string from the original array to a string. */
  char tb_inString[6];
  for (int i = 0; i < ct_array; i++)
    tb_inString[i] = tb[i] + '0'; /* Syntax for converting an int to a char. */
  
  tb_inString[5] = '\0'; /* Strings have this null value on the last element of the array.*/
  
  if (strcmp(tb_inString, "55555") == 0){
        *score += 15;
        printf("\nYatzy! Score: %d", *score);
        return 1;
  }
  printf("\nNo Yatzy. Score: %d", *score);
  return 0;
}

/* Compares two numbers and returns ints to qsort, which it will interpret. */
int n_cmp(const void *ep1, const void *ep2){
  int *tp1 = (int *)ep1, *tp2 = (int *)ep2;
  if (*tp1 < *tp2)
    return -1;
  else if (*tp1 > *tp2)
    return 1;
  else
    return 0;
}

void get_score(const int tb[], const int dies_total, int *score, int round){
  int pairs, kinds, straights, fullHouses, chances, yatzies;
  /* Upper section with 1-6. */
  if (round == 1){
    for (int i = 1; i <= 6; i++)
      printf("Number %d: %d\n", i, alike(tb, dies_total, &*score, i)); 
  } else if (round == 2){       /* Lower section. Returns the commented values.*/ 
      pairs = pair(tb, dies_total, &*score); /* Number of pairs. */
  } else if (round == 3){
      kinds = ofAKind(tb, dies_total, &*score); /* Four kinds: 4, Three kinds: 3 and None: 0. */
  } else if (round == 4){
      straights = straight(tb, dies_total, &*score); /* Small: -1, Large: 1 and None: 0. */
  } else if (round == 5){
      fullHouses = fullHouse(tb, dies_total, &*score, pairs, kinds); /* Full house: 1, None: 0. */
  } else if (round == 6){
      chances = chance(tb, dies_total, &*score); /* Completed: 1 */
  } else if (round == 7){
      yatzies = yatzy(tb, dies_total, &*score); /* Yatzy: 1, None 0. */
  }
}

int main(void){
  time_t t;
  srand((unsigned)time(&t));

  int dies_total = promt();
  int *tb = roll_multiple_dies(dies_total);
  int score = 0;

  /* Sorts the array with the qsort algorithm, (takes the 5 biggest numbers*) and prints it out. */
  qsort(tb, dies_total, sizeof(int), n_cmp);
  for (int k = 0; k < dies_total; k++)
    printf("%d  ", tb[k]);
  printf("\n");

  for (int rounds = 1; rounds <= 8; rounds++)
    get_score(tb, dies_total, &score, rounds)
  ;/*
  draw_scoreboard();
  play_again();*/

  return 0;
}