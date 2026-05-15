/*
Pick a hardcoded secret number,
(use a random library with prompted
seed instead)
loop on `scanf` until the user guesses it,
print higher/lower hints.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Welcome to random guesser!\n");
	int guess, seed, max_num;
	//get max num
	printf("Give me random number ceiling\n");
	scanf("%d", &max_num);
	//get seed and rn
	printf("Seed the RNG\n");
	scanf("%d", &seed);
	srand(seed);
	int num = (rand() % max_num) + 1;
	while(guess != num) {
		//get guess
		printf("Give me a guess\n");
		scanf("%d", &guess);
		//print hint or gz
		if (guess < num) {
			printf("Higher, ");
		}
		else if (guess > num) {
                        printf("Lower, ");
                }
		else if (guess == num) {
			printf("Congrats! That's correct\n");
		}
	}
	return 0;
}
