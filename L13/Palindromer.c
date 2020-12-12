#include <stdio.h>
#include <string.h>

int is_palindrome_iter(char *str){
  for (int i = 0; i < strlen(str); i++){
    if (str[i] != str[strlen(str) - i - 1])
      return 0;
  }
  return 1;
}

int is_palindrome_rec(char *str){
  int len_str = strlen(str);

  char new_str[len_str];
  strncpy(new_str, str + 1, len_str - 2);

  int new_len_str = strlen(new_str);
  // printf("len: %d ", len_str);
  if (new_len_str == 1)
    return 1;
  else if (str[0] == str[len_str-1]){
    // printf("str: %s\n", new_str);
    return is_palindrome_rec(new_str);
  }
  return 0;
}

int main(void){
  //printf("IsPalindrom: %d", is_palindrome_iter("regninger"));
  printf("IsPalindrom: %d", is_palindrome_rec("racecar"));
}