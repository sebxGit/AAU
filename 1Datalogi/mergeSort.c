#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

void Merge(int L[], int start, int slut, int midt);
void MergeSort(int L[], int start, int slut);
void printList(int L[], int size);

int main(void){ 
  int L[] = { 5, 3, 8, 1, 6, 10, 7, 2, 4, 9}; 
  int L_size = sizeof(L) / sizeof(L[0]); 
  	
  printf("Givet listen \n"); 
  printList(L, L_size); 
  MergeSort(L, 0, L_size - 1); 
  
  printf("Er den sorterede liste \n"); 
  printList(L, L_size); 
  return 0; 
} 

void Merge(int L[], int l, int r, int m){
  /* Start med at kopiere de to dellister ind i to nye lister L1 og L2, så vi ikke sletter nogle elementer fra L når vi begynder at flette elementerne derind */
  int a = m - l + 1;
  int b = r - m;
  int i = 0, j = 0, k;
  int* L1 = (int*) malloc(a * sizeof(int*));
  int* L2 = (int*) malloc(b * sizeof(int*));
  if(L1 == NULL || L2 == NULL){
    printf("Could not allocate enough memory. Bye");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < a; i++){
    L1[i] = L[l + i];
  }

  for (int i = 0; i < b; i++){
    printf("%d", i - (m + 1));
    L2[i] = L[m + 1 + i];
  }
  i = j = 0, k = l;

  /* Herefter skal vi kopiere elementer fra L1 og L2 ind på pladserne i L mellem start og slut men i sorteret rækkefølge */
  while(i < a && j < b){
    if (L1[i] <= L2[j]){
      L[k] = L1[i];
      i++;
    }
    else {
      L[k] = L2[j];
      j++;
    }
    k++;
  }
  // j == r - m
  if (j == b){
    while(i++ < a){
      L[k] = L1[i - 1];
      k++;
    } 
  }else{
    while(j++ < b){
      L[k] = L2[j - 1];
      k++;
    }
  }
  free(L1);
  free(L2);
}


void MergeSort(int L[], int start, int slut){
  /* Udfyld her */
  if (start < slut){
    int m = floor((slut + start) / 2);
    MergeSort(L, start, m);
    MergeSort(L, m + 1, slut);
    Merge(L, start, slut, m);
  }
}

void printList(int L[], int size){ 
  int i; 
  for (i = 0; i < size; i++) 
    printf("%d ", L[i]); 
  printf("\n"); 
}