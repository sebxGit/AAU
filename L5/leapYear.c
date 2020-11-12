#include <stdio.h>

int isLeapYear();

int main(){
  for(int y = 1900; y <= 2100; y++){
    if(isLeapYear(y) != 0)
    printf("%d\n", isLeapYear(y));
  }
}
 
int isLeapYear(int year){
  int res;
  if (year % 400 == 0)
    res = year;
  else if (year % 100 == 0)
    res = 0;
  else if (year % 4 == 0)
    res = year;
  else res = 0;
  return res;
}

