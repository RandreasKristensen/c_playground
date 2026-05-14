#include <stdio.h>

void fizzbuzz(int x);

int main(void) {
	printf("welcome to fizzbuzz, please pick a number\n");
	int a;
	scanf("%d", &a);
	fizzbuzz(a);
	return 0;
}

int divisible(int a, int b);

void fizzbuzz(int x) {
	for(int i = 1; i <= x; ++i) {
		if(!divisible(i,3) && !divisible(i,5)) printf("%d, ", i);
		if(divisible(i,3) && divisible(i,5)) printf("fizzbuzz, ");
		if(divisible(i,3) && !divisible(i, 5)) printf("fizz, ");
		if(!divisible(i,3) && divisible(i,5)) printf("buzz, ");
	}
	printf("\n");
}

int divisible(int a, int b) {
	if(a%b==0) return 1;
	else return 0;
}
