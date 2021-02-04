#include <stdio.h>
#include <math.h>

int getInput(){
  int secs;
  printf("How many seconds as an integer do you want?\n >>");
  scanf("%d", &secs);
  return secs;
}

int main(){
  int mins, hrs, days, weeks;
  int secs = getInput();

  mins = secs / 60;
  secs %= 60;
  hrs = mins / 60;
  mins %= 60;
  days = hrs / 24;
  hrs %= 24;
  weeks = days / 7;
  days %= 7;

  printf("%d weeks, %d days, %d hours, %d minutes, %d seconds", weeks, days, hrs, mins, secs);
  return 0;
}
