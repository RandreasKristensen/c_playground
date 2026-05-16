/*
Write a `swap(int *a, int *b)` function 
and call it. Then do the same for strings 
(char pointers).
Goal: actually feel the difference 
between pass-by-value and pass-by-pointer.
*/

#include <stdio.h>

void ptr_swap_char(char* a, char* b);
void ptr_swap_int(int* a, int* b);

int main(void) {
	int a = 1;
	int b = 2;
	printf("before swap a: %d, b: %d\n", a, b);
	ptr_swap_int(&a, &b);
	printf("after swap a: %d, b: %d\n", a, b);
	return 0;
}

void ptr_swap_char(char* a, char* b) {
	char temp_a = *a;
	*a = *b;
	*b = temp_a;
}

void ptr_swap_int(int* a, int* b) {
	int temp_a = *a;
	*a = *b;
	*b = temp_a;
}
