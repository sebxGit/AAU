#include <stdio.h>
#define BRO_LENGTH 670;

typedef struct {
  double acceleration;
  double max_speed;
  double position;
} car;

double ms_to_kmt(double x){
  return x * 3.6;
}

double kmt_to_ms(double x){
  return x / 3.6;
}

int main(){
  int i = 0;

  double velocity = 10;
  velocity = ms_to_kmt(velocity);

/*
  car car1 = {2, 50, 0}; 
  printf("%lf, %lf, %lf\n", car1.acceleration, car1.max_speed, car1.position);

  for (car1.position; car1.position < BRO_LENGTH){
    printf("PrevPos: %lf  ", car1.position);

    car1.position += car1.max_speed*1000/3600;
    i++;

    printf("PostPos: %lf\n", car1.position);
  }
  printf("Took %d secs", i);
*/
  return 0;
}
