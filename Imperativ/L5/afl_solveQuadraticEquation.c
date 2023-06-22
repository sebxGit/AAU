#include <stdio.h>
#include <math.h>

/* Prints roots of the quadratic equation a * x*x + b * x + c = 0 */

/* Tre nye funktioner: solveDiscriminant(), solveRootOne(), solveRootTwo()
   
   While-løkke som kører indtil a = 0, b = 0 og c = 0. 
   Kontrolstruktur som springer over print hvis a = 0, b = 0 og c = 0  
   (if-statementet er under solveQuadraticEquation) */
double solveDiscriminant(double a, double b, double c){
    return b * b - 4 * a * c;
}

double solveRootOne(double a, double b, double c, int discriminant){
    double root1;
    if (discriminant == 0){
        root1 = -b/(2*a);
    }else{
        root1 = (-b + sqrt(discriminant))/(2*a);
    }
    return root1;
}

double solveRootTwo(double a, double b, double c, double discriminant){
    return (-b - sqrt(discriminant))/(2*a);
}

void solveQuadraticEquation(double a, double b, double c){
  double discriminant, root2;

  discriminant = solveDiscriminant(a, b, c);

  if (a == 0 && b == 0 && c == 0){
      printf("You exited the program.");
      return;}
  else if (discriminant < 0)
    printf("No roots\n");
  else if (discriminant == 0){
      double root1 = solveRootOne(a, b, c, 0);
      printf("One root: %f\n", root1);
  }
  else {
      double root1 = solveRootOne(a, b, c, discriminant);
      double root2 = solveRootTwo(a, b, c, discriminant);
      printf("Two roots: %f and %f\n", root1, root2);
  }

}   

int main(void) {
  double a, b, c;
  
  while (a != 0 && b != 0 && c != 0){
      printf("Enter coeficients a, b, and c: ");
      scanf("%lf %lf %lf", &a, &b, &c);
      solveQuadraticEquation(a, b, c);
  }

  return 0;
}

// Lavet af Sebastian Truong A409, Aalborg Universitet