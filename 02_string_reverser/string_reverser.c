/*
Take a string literal, reverse it in-place
using a char array and two-pointer swap.
Reminds you of: arrays, pointers, indexing,
null terminator, strlen.
*/

#include <stdio.h>
#include <string.h>

void string_reverser(char* string);

int main(void) {
	printf("give me a string literal\n");
	char string_literal[64];
	scanf("%s", string_literal);
	string_reverser(string_literal);
	printf("reversed: %s\n", string_literal);
	return 0;
}

void string_reverser(char* start_of_string) {
	//we need two pointer:
		//start of string (we have)
		//end of atring
	char* end_of_string =
		start_of_string + strlen(start_of_string) - 1;
	//then we make the char at the
	//addresses swap place, then move the
	//pointers toward the middle,
	//until they point to the same place,
	// or have moved past each other.
	while(start_of_string < end_of_string) {
		char temp = *start_of_string;
		*start_of_string = *end_of_string;
		*end_of_string = temp;
		start_of_string++;
		end_of_string--;
	}
}
