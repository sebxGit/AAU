#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int arr[30] = {1,4,5,7,3,6,9};
	qsort(arr);
	return 0;
}

int* qsort(int arr[]){
	int* j = malloc(15*sizeof(int));
	int* k = malloc(15*sizeof(int));
	if(!j || !k){printf("ERROR!"); exit(0);}
	memcpy(j, arr, 3 * sizeof(int));
	memcpy(j, arr+3, 3 * sizeof(int));
	//int pivot = arr[6];
	for(int i = 0; i< 15; i++){
		printf("%d",j[i]);
	}
}