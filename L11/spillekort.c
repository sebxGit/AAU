#include <stdio.h>
#include <stdlib.h>
#define MAX_CARDS 55
#define NUMBER_OF_SYMBOLS 4
#define NUMBER_OF_JOKERS 3

typedef struct{
  char *symbol, *type;
  int value;
} Playingcard;

Playingcard make_card(char *symbol, char *type, int value){
  Playingcard result;
  result.symbol = symbol;
  result.type = type;
  result.value = value;
  return result;
}

void show_cards(Playingcard set){
  printf("Symbol: %s\n"
         "Type: %s\n"
         "Value: %d\n"
         "-----------\n",
         set.symbol, set.type, set.value);
}

char* give_symbol(int s, char* symbol){
  switch(s) { /* I rækkefølge: spar, klør, ruder, hjerter */
    case 0: symbol = "Clubs"; break;
    case 1: symbol = "Diamonds"; break;
    case 2: symbol = "Hearts"; break;
    case 3: symbol = "Spades"; break;
  }
  return symbol;
}

int main(void){
  Playingcard set[MAX_CARDS];
  char* symbol;
  int s = 0;

  for(int num = 0; num < 56; num++){
    if (num % 13 == 0){
      symbol = give_symbol(s, symbol);
      s++;
    }
    if (num % 13 < 9 && num < 52){
      set[num] = make_card(symbol, "Num", 2 + (num % 13));
    }else if (num < 52){
      if (num % 13 == 9)
        set[num] = make_card(symbol, "Knight", 2 + (num % 13));
      else if (num % 13 == 10)
        set[num] = make_card(symbol, "Lady", 2 + (num % 13));
      else if (num % 13 == 11)
        set[num] = make_card(symbol, "King", 2 + (num % 13));
      else if (num % 13 == 12)
        set[num] = make_card(symbol, "Ace", 2 + (num % 13));
    }else 
      set[num] = make_card("None", "Joker", 15);
  }
  for(int i = 0; i < 56; i++)
    show_cards(set[i]);
}