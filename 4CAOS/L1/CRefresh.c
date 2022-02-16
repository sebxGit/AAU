#include<stdio.h>
void printArray(long array[]){
	for(int i = 0; i < 20; i++){
		printf("%lu %lx \n", array[i], array[i]);
	}
}

void swap(long *ptr, long *ptr2){
	long temp = *ptr;
	*ptr = *ptr2;
	*ptr2 = temp;
}

int main(){
	long arr[20];
	for(int i = 0; i < 20; i++){
		arr[i] = 10+i;
	}
	printArray(arr);
  
	long *x = &arr[3];
	printf("Pointer address *x: %p\n", *&x);

	printf("x deref: %d\n", arr[3]);

	long *p1 = &arr[0];
	long *p2 = &arr[5];
	swap(p1, p2);
	printArray(arr);

	long y = *(x+9);
	printf("Hex: %x\n", &y);
	y = *(x+100);
	printf("Hex with *(x+100): %x\n", &y);
	y = *(x+100000);
	printf("Hex with *(x+100000): %x\n", &y); //overflow
}

