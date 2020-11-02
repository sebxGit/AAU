#include <stdio.h>

double pop, growth, popMax; // Pop: 9870, Growth: 1.1, popMax: 30000

int populationProjection(double pop, double growth, double popMax){
  int y;
  for (y = 0; pop <= popMax; y++){
    pop *= growth;
  }
  return y;
}

int main(){
  printf("Please type the population, population growth percentage and max population.\n");
  scanf("%lf %lf %lf", &pop, &growth, &popMax);
  printf("The year it hits the max population is year %d.", populationProjection(pop, growth, popMax));

  return 0;
}
