#include<stdio.h>

void inplace_swap(int *x, int *y){
	*y = *x ^ *y; //step1
	printf("%d, %d\n", *x, *y);
	*x = *x ^ *y; //step2
	printf("%d, %d\n", *x, *y);
	*y = *x ^ *y; //step3
	printf("%d, %d\n", *x, *y);
}

int main(){
	int *a;
	int *b;
	int k = 1;
	int j = 0;
	a = &k;
	b = &j;
	inplace_swap(a, b);
}
