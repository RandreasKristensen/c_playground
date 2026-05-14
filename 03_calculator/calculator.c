/*
Read two numbers and an operator
from stdin with `scanf`,
do the math, print the result.
Reminds you of: scanf, switch/case, basic I/O,
handling division by zero.
*/

#include <stdio.h>

int calculator(int a, int b, char op, int *result);

int main(void) {
	printf("give me numbers a and b and an operator\n");
	int a, b;
	char op;
	int result;
	printf("a: ");
	fflush(stdout);
	scanf("%d", &a);
	printf("b: ");
	fflush(stdout);
	scanf("%d", &b);
	printf("operator: ");
	fflush(stdout);
	scanf(" %c", &op);
	int err = calculator(a, b, op, &result);
	if (!err) printf("result: %d\n", result);
	return 0;
}

int calculator(int a, int b, char op, int *result) {
	switch(op) {
		case('+'):
			*result = a+b;
			return 0;
			break;
		case('-'):
			*result = a-b;
                        return 0;
			break;
                case('/'):
			if(b == 0) {
				printf("cannot divide by 0");
				return 2;
			}
			*result = a/b;
                        return 0;
                        break;
                case('*'):
			*result = a*b;
                        return 0;
                        break;
		default:
			printf("unknown operator");
			return 1;
			break;
	}
	return 0;
}
