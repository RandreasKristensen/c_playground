/*
Read two numbers and an operator
from stdin with `scanf`,
do the math, print the result.
Reminds you of: scanf, switch/case, basic I/O,
handling division by zero.
*/

#include <stdio.h>

// so I imagine like a, b, op as args
int calculator(int a, int b, char op, int *result);

/*
int result;
int err = calculate(a, b, op, &result);

if (err == ERR_DIV_ZERO) printf("error: division by zero\n");
else if (err == ERR_BAD_OP) printf("error: unknown operator\n");
else printf("result: %d\n", result);

*/
int main(void) {
	printf("give me numbers a and b and an operator\n");
	int a, b;
	char op;
	int *result;
	printf("a: ");
	scanf("%d\n", &a);
	printf("b: ");
	scanf("#%d\n", &b);
	printf("operator: ");
	scanf("%c\n", &op);
	return 0;
}

int calculator(int a, int b, char op, int *result) {
	switch(op) {
		case('+'):
			return 0;
			break;
		case('-'):
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
                        return 0;
                        break;
		case('%'):
			return 0;
			break;
		default:
			printf("unknown operator");
			return 1;
			break;
	}
	return 0;
}
