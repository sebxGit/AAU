#include <stdio.h>
#include <math.h>

int main(){
  // Definerer tidsenhederne
  int secs, mins, hrs, days, weeks;

  // Spørger brugeren om antal sekunder og spørger om et heltals-input
  printf("How many seconds as an integer do you want?\n >>");
  scanf("%d", &secs);

  // Her beregnes sekunder om til respektivt minutter, timer, dage, uger
  // ved at dele den større tidsenhed med 60 el. 24 el. 7 (alt efter størrelse)
  //, hvorefter modulus svarer til den resterende antal tid af tidsenheden.
  mins = secs / 60;  // Hvor mange minutter per 60. sekund
  secs %= 60; /* Resten svarer til antal sekunder.
                 Processen fortsætter indtil programmet er nået til uger*/
  hrs = mins / 60; 
  mins %= 60;
  days = hrs / 24;
  hrs %= 24;
  weeks = days / 7;
  days %= 7;

  // Printer de respektive tidsenheder op i en opstillet printf funktion med tidsenhederne
  // i rækkefølge efter størrelse, størst mod mindst.
  printf("%d weeks, %d days, %d hours, %d minutes, %d seconds", weeks, days, hrs, mins, secs);
  return 0;
}

// Kodet af Sebastian Truong, grp. 311b, Aalborg Universitet