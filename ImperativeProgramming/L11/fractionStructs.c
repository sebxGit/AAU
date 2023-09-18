#include <stdio.h>

/* Only positive fractions. My program does not return any values and
   I used struct a1 as the result and a2 to manipulate the value of a1.*/
typedef struct{
  unsigned int numerator;
  unsigned int denominator;
} fraction;

void reduceFraction(fraction *a1){
  int numeratorBigger, smallestElementInFraction;
  if (a1->numerator % a1->denominator == 0 || a1->denominator % a1->numerator == 0){
    numeratorBigger = (a1->numerator > a1->denominator) ? 1 : 0;
    if (numeratorBigger){
      a1->numerator /= a1->denominator;
      a1->denominator = 1;
    }else{
      a1->denominator /= a1->numerator;
      a1->numerator = 1;
    }
  }else{
    smallestElementInFraction = (a1->numerator < a1->denominator) ? a1->numerator : a1->denominator;
    for (int i = 1; i < smallestElementInFraction; i++){
      if (a1->numerator % i == 0 && a1->denominator % i == 0){
        a1->numerator /= i;
        a1->denominator /= i;
      }
    }
  }
}

void displayFraction(fraction *a1, char* msg){
  printf("\nFraction %s %d/%d", msg, a1->numerator, a1->denominator);
}

void multiplyFractionWithInt(fraction *a1, int wholeNumber){
  a1->numerator *= wholeNumber;
  reduceFraction(a1);
}

void multiplyFractionwithFraction(fraction *a1, fraction *a2){
  a1->numerator *= a2->numerator;
  a1->denominator *= a2->denominator;
  reduceFraction(a1);
}

void addFractionWithFraction(fraction *a1, fraction *a2){
  if (a1->numerator == 1 && a1->denominator == 1 || 
      a2->numerator == 1 && a2->denominator == 1)
    return;
  else{
    /* By formula a/b + c/d = (ad+cb)/bc for every fraction. */
    a1->numerator = (a1->numerator * a2->denominator) + (a2->numerator * a1->denominator);
    a1->denominator *= a2->denominator;
  }
  reduceFraction(a1);
}

int main(void){
  fraction a1 = {5,15};
  fraction a2 = {3,10};
  int wholeNumber = 5;
  printf("Fraction: %d/%d, Fraction 2: %d/%d, int: %d", a1.numerator, 
         a1.denominator, a2.numerator, a2.denominator, wholeNumber);
  /*reduceFraction(&a1);
  displayFraction(&a1, "reduced: ");
  multiplyFractionWithInt(&a1, wholeNumber);
  displayFraction(&a1, "multiplied and reduced: ");
  multiplyFractionwithFraction(&a1, &a2);
  displayFraction(&a1, "multiplied with fraction a2: ");
  addFractionWithFraction(&a1, &a2);
  displayFraction(&a1, "added with fraction a2: ");*/

  return 0;
}