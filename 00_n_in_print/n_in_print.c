#include "stdio.h"
#include "string.h"

int main(void) {
	printf("n_in_print starting... \n\n");

	char input[256];
	printf("taking input:\n");
	fgets(input, sizeof(input), stdin);

	printf("input read:\n");
	printf("%s",input);

	return 0;
}
