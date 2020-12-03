#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Sebastian Truong, Grp. A409, Aalborg Universitet Software 1. semester 2020 */

/* Hjælpeværktøjer:
     - Nettet til at se eksempler på dynamisk allokering, continue, strcmp 
     - Linje 81 - 85 fra "Videoer I Lektion 9: "Statisk og dynamisk lagerallokering" - Kurt Nørmark
*/
     
/* This program plays yatzy with itself. Proceedes with the rounds and prints final score and 
   bonus points. Asks if you want to try again.
   

   Notice:
   My program does not implement the rule: At least 3 alike dice rolls to add points.
*/


int prompt();
int n_cmp(const void *ep1, const void *ep2);
int *roll_multiple_dies(int ct);
void get_score(const int tb[], const int dies_total, int *score, int round, int *bonus_points);
int alike(const int tb[], const int dies_total, int *score, const int i);
void pair(const int tb[], const int dies_total, int *score);
void threeOfAKind(const int tb[], const int dies_total, int *score);
void fourOfAKind(const int tb[], const int dies_total, int *score);
void smallStraight(const int tb[], const int dies_total, int *score);
void largeStraight(const int tb[], const int dies_total, int *score);
void fullHouse(const int tb[], const int dies_total, int *score);
void chance(const int tb[], const int dies_total, int *score);
void yatzy(const int tb[], const int dies_total, int *score);
void final_score(int score, int bonus_points);
int try_again();

int main(void){
  time_t t;
  srand((unsigned)time(&t));
  int score = 0, bonus_points = 0;
  int running = 1;

  while (running){
    int dies_total = prompt(); /* Returns n count of wanted die rolled. */

    for (int rounds = 1; rounds <= 9; rounds++){
      int *tb = roll_multiple_dies(dies_total);
      get_score(tb, dies_total, &score, rounds, &bonus_points);
      free(tb);
    }
    final_score(score, bonus_points);
    running = try_again();
    }
  return 0;    
}

int prompt(){
  int dies_called = 0;

  do{
    printf("How many dies do you want to throw over 5?\n");
    scanf("%d", &dies_called);
    } while (dies_called < 5);
  printf("\n");
  return dies_called;
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

int *roll_multiple_dies(const int dies_total){
  int *tb = (int *)malloc(dies_total * sizeof(int));
  if (tb == NULL){
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < dies_total; i++)
    tb[i] = 1 + ((int)rand() % 6); /* Dice Roll */ 

  /* Sorts the array with the qsort algorithm in an ascending order. */
  qsort(tb, dies_total, sizeof(int), n_cmp);

  /* Prints the numbers.*/
  for (int k = 0; k < dies_total; k++)
    printf("%d  ", tb[k]);
  return tb;
}

void get_score(const int tb[], const int dies_total, int *score, int round, int *bonus_points){
  /* Upper section with 1-6. */
  if (round == 1){              
    printf("Number %d: Amount: %d, Score: %d\n", 1, alike(tb, dies_total, &*score, 1), *score);
    for (int i = 2; i <= 6; i++){
      int* tb = roll_multiple_dies(dies_total);
      printf("Number %d: Amount: %d, Score: %d\n", i, alike(tb, dies_total, &*score, i), *score);
    }
    if (*score >= 63)
      *bonus_points = 50;
  }  
  /* Lower section.*/ 
  else if (round == 2){      
      pair(tb, dies_total, &*score); 
  } else if (round == 3){
      threeOfAKind(tb, dies_total, &*score);
  } else if (round == 4){
      fourOfAKind(tb, dies_total, &*score);
  } else if (round == 5){
      smallStraight(tb, dies_total, &*score); 
  } else if (round == 6){
      largeStraight(tb, dies_total, &*score); 
  } else if (round == 7){
      fullHouse(tb, dies_total, &*score); 
  } else if (round == 8){
      chance(tb, dies_total, &*score);
  } else if (round == 9){
      yatzy(tb, dies_total, &*score);
  }  
  printf("\n");
}

int alike(const int tb[], const int dies_total, int *score, const int i){
  int ct = 0; /* Counts of the occurences of the num. */
  for (int a = 0; a < dies_total; a++){
    if (tb[a] == i){
      *score += i;
      ct += 1;
      if (ct == 5)
        break;
    }
  }
  return ct;
}

void pair(const int tb[], const int dies_total, int *score){
  int prev_num = -1, pairs = 0, highest_pair = 0; 
    for (int i = dies_total; i > 0; i--){ /* Compares for all, two adjacent numbers and identifies pairs. */
      if (prev_num == tb[i - 1]){ 
        if (!highest_pair)
          highest_pair = prev_num;
        pairs += 1;
        *score += tb[i] + prev_num;
        i--;
      }   
    if (pairs == 2) /* Max two pairs in a set of 5 dices. */
      break;
    else 
      prev_num = tb[i - 1];
    } 
  printf("Pairs: %d, Score: %d  (Highest 2 pairs)", pairs, *score);
}

void threeOfAKind(const int tb[], const int dies_total, int *score){
  /* Compares for all elements, if three adjacent elements are equal.*/
  for (int i = dies_total; i > 0; i--){
    if (tb[i] == tb[i-1] && tb[i] == tb[i - 2]){
      *score += tb[i] * 3;
      printf("Three of a kind: Num %d, Score: %d", tb[i], *score);
      return;
    }
  } 
  printf("Three of a kind: Score: %d", *score);
}

void fourOfAKind(const int tb[], const int dies_total, int *score){
  /* Compares for all elements, if four adjacent elements are equal.*/
  for (int i = dies_total; i > 0; i--){
    if (tb[i] == tb[i - 1] && tb[i] == tb[i - 2] && tb[i] == tb[i - 3]){
      *score += tb[i] * 4;
      printf("Four of a kind: Num %d, Score: %d", tb[i], *score);
      return;
    }
  }
  printf("Four of a kind: Score: %d", *score);
}

void smallStraight(const int tb[], const int dies_total, int *score){
  /* Creates new string tb_instring[] from tb[], then a non-dublicate of tb_instring[] called tb_sorted[]. */

  /* Making a new string from the original array to a string. */
  char tb_inString[dies_total + 1];
  for (int i = 0; i < dies_total; i++)
    tb_inString[i] = tb[i] + '0'; /* Syntax for converting an int to a char. */
  
  tb_inString[dies_total] = '\0'; /* Strings have this null value on the last element of the array. */

  /* Creates a string from the previous string but without dublicates. */
  int prev_num = -1, n = 0;
  char tb_sorted[7]; /* Only 6 possible numbers on dice and in total 7 with null character (string). */
  for (int i = 0; i < dies_total; i++){
    if (tb_inString[i] == prev_num)
      continue;
    tb_sorted[n] = tb_inString[i];
    prev_num = tb_inString[i];
    n++;
  }
  tb_sorted[6] = '\0'; 

/* Checks if the non-dublicate string gives a small straight or not. */
if (strcmp(tb_sorted, "12345") == 0){
    *score += 15;
    printf("Small Straight! Score: %d", *score);
  }else
    printf("No Small Straight. Score: %d", *score);
}

void largeStraight(const int tb[], const int dies_total, int *score){
  /* Same process as at the smallStraight function. */
  char tb_inString[dies_total + 1];
  for (int i = 0; i < dies_total; i++)
    tb_inString[i] = tb[i] + '0';
  
  tb_inString[dies_total] = '\0';
  
  int prev_num = -1, n = 0;
  char tb_sorted[7];
  for (int i = 0; i < dies_total; i++){
    if (tb_inString[i] == prev_num)
      continue;
    tb_sorted[n] = tb_inString[i];
    prev_num = tb_inString[i];
    n++;
  }
  tb_sorted[6] = '\0';

  if (strcmp(tb_sorted, "23456") == 0 || strcmp(tb_sorted, "123456") == 0){
    *score += 20;
    printf("Large Straight! Score: %d", *score);
  } else
    printf("No Straights. Score: %d", *score);
}

void fullHouse(const int tb[], int dies_total, int *score){
  int three_kind = 0, pair = 0, prev_num = -1;

  /* Finds three alike first. */
  for (int i = dies_total; i > 0; i--){
    if (tb[i] == tb[i-1] && tb[i] == tb[i - 2]){
      three_kind = tb[i];
      break;
    }
  }

  /* Then a pair. */
  for (int i = dies_total; i > 0; i--){
    if (prev_num == tb[i - 1]) {
      pair = tb[i - 1]; 
      break;
    }else 
      prev_num = tb[i - 1];
  } 

  /* Only Full House if both pair and three_kind are present. */
  if (pair > 0 && three_kind > 0){
    *score += pair * 2 + three_kind * 3;
    printf("Full House! Score %d", *score);
  } else{
    printf("No Full House. Score: %d", *score);
  }
}

void chance(const int tb[], const int dies_total, int *score){
  /* Adds the five highest numbers to score. */
  for (int i = 0; i < dies_total; i++){
    *score += tb[dies_total - i - 1];
    if (i == 4)
      break;
  }
  printf("Chance! Score: %d", *score);
}

void yatzy(const int tb[], const int dies_total, int *score){
  /* Checks if, for all elements, five adjacent elements are equal. */
  for (int i = dies_total; i > 0; i--){
    if (tb[i] == tb[i - 1] && tb[i] == tb[i - 2] && tb[i] == tb[i - 3] && tb[i] == tb[i - 4]){
      *score += tb[i] * 5;
      printf("Yatzy! Num %d, Score: %d", tb[i], *score);
      break;
    } else if (i == 1){
      printf("No Yatzy. Score: %d", *score);
    }
  }
}

void final_score(int score, int bonus_points){
  score += bonus_points;
  printf("Final Score: %d\n", score);
  printf("Bonus points awarded: %d\n", bonus_points);
}

int try_again(){
  char ans[1];
  do{
  printf("\nDo you wish to try again? (y/n) ");
  scanf("%s", ans);
  } while (!(strcmp(ans, "y") == 0 || strcmp(ans, "n") == 0));
  
  if (strcmp(ans, "y") == 0)
    return 1;
  else
    return 0;
}
