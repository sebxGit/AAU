#include<stdio.h>
int main(){
	printf("--Start--\n");
	unsigned char a=0x55;
	unsigned char b=0x46; 
	printf("a & b %x\n", a & b);
	printf("a | b %x\n", a | b);
	printf("a & b %x\n", ~a | ~b);
	printf("a & b %x\n", a & !b);
	printf("a & b %x\n", a && b);
	printf("a & b %x\n", a || b);
	printf("a & b %x\n", !a || !b);
	printf("a & b %x\n", a && ~b);
}