#include <stdio.h>
#include <math.h>

int main(){
  // Definerer tidsenhederne
  int secs, mins, hrs;

  // Spørger brugeren om antal sekunder og spørger om et heltals-input
  printf("How many seconds do you want?\n >>");
  scanf("%d", &secs);

  /* Her beregnes sekunder om til respektivt minutter, timer, dage, uger
     ved at dele den større tidsenhed med 60 (alt efter størrelse)
     hvorefter modulus svarer til den resterende antal tid af tidsenheden.*/
  mins = secs / 60;  // Hvor mange minutter per 60. sekund
  secs %= 60; /* Resten svarer til antal sekunder.
                 Processen fortsætter indtil programmet er nået til uger*/
  hrs = mins / 60;
  mins %= 60;

  /*Printer de respektive tidsenheder op i en opstillet printf funktion med tidsenhederne
    i rækkefølge efter størrelse, størst mod mindst. Tager betingelserne for at
    tidsenheden og ændre stringen til respektivt ental, ikke printe string ud da
    tidsenheden er nul og flertal. Printer error, hvis ikke gyldigt input.
    */
  (hrs == 1)? printf("%d hour, ", hrs) : (hrs == 0) ?: (hrs > 1) ? printf("%d hours, ", hrs) : printf("ERROR: Hours \n");
  (mins == 1)? printf("%d minute", mins) : (mins == 0) ?: (mins > 1) ? printf("%d minutes", mins) : printf("ERROR: Minutes \n");
  (mins > 0)? printf(" og "): mins; // Skriver 'og' hvis der er minutter og timer og der er en opremsning.
  //Compileren vil have et argument efter else, så jeg putter mins ind som ikke gør noget
  (secs == 1)? printf("%d second, ", secs) : (secs == 0) ? printf("0 seconds"): (secs > 1) ? printf("%d seconds, ", secs) : printf("ERROR: Seconds \n");
  return 0;

}

// Kodet af Sebastian Truong, grp. 311b, Aalborg Universitet
