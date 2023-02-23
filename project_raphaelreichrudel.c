#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define ZERO 0
#define ONE 1
#define FIVE 5

#define EASY 1

#define CONVERT_TO_ASCII 48

#define WIN 4

#define STOP 'n'
#define CONTINUE 'y'

int code = 0;
int firstDigit, secondDigit, thirdDigit, fourthDigit = 0;

int crazyFlag = 0;

enum difficultyLevel{easy = EASY, medium, hard, crazy};

void welcomeMessage(void);
int isValidCode(int code);

void play(int attempts);
int checkInput(int digit);

int lose(int hits, int misses);
int win(int attemptCount);

int main(void)
{
	code = 0;
	
	enum difficultyLevel difficulty = 0;
	
	int attempts = 0;
	
	const int CRAZY_MIN = 5;
	const int CRAZY_MAX = 25;
	
	const int MIN = 1111;
	const int MAX = 6666;
	
	srand(time(NULL));
	
	int ans = 0;
	
	code = rand() % (MAX - MIN + ONE) + MIN;
	
	ans = isValidCode(code);
	
	while (ans != ONE) { // keep generating a code if it's not valid
		code = rand() % (MAX - MIN + ONE) + MIN;
		ans = isValidCode(code);
	}
	
	// if you want to see the code's value, add a printf("%d", code) here :)
	
	welcomeMessage();
	
	printf("You have four difficulty levels:\n1 - Easy (20 guesses)\n2 - Medium (15 guesses)\n3 - Hard (10 guesses)\n4 - Crazy (Random number of guesses from 5 to 25)\n\n");
	
	printf("Please enter your preferred difficulty level: ");
	scanf("%d", &difficulty);
	
	getchar();
	
	while (difficulty <= ZERO || difficulty >= FIVE) { // checks the validation of the input of the difficulty
		printf("\nError! You must pick a valid option. ");
		scanf("%d", &difficulty);
		
		getchar();
	}
	
	switch (difficulty) {
		case easy:
			attempts = 20;
			play(attempts);
			break;
		case medium:
			attempts = 15;
			play(attempts);
			break;
		case hard:
			attempts = 10;
			play(attempts);
			break;
		case crazy:
			crazyFlag = 1;
			attempts = rand() % (CRAZY_MAX - CRAZY_MIN + ONE) + CRAZY_MIN;
			play(attempts);
			break;
	}
	
    return 0;
}

/**
This function prints a nice little welcome message.
input: none
output: none
*/

void welcomeMessage(void) {
	printf("\nWelcome to Hannuka Code Breaker, by Raphael Reichrudel!\n\n");
	
	printf("A secret password was chosen to protect the credit card of Pancratius, the descendant of Antiochus.\nYour mission is to stop Pancratius by revealing his secret password.\n\n");
	printf("The rules are as follows:\n");
	
	printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
	printf("2. After every guess you'll receive two hints about the password\n   HITS:   The number of digits in your guess which were exactly right.\n   MISSES: The number of digits in your guess which belongs to\n           the password but were miss-placed.\n");
	printf("3. If you'll fail to guess the password after a certain number of rounds\n   Pancratius will buy all the gifts for Hanukkah!!!\n\n");
}

/**
This function generates a valid code - first it checks that its digits are in the range of 1 to 6, then it checks if there's a duplicate digit
input: code - a random generated number, that ranges from 1111 to 6666
output: ans, an integer that is 1 if the conditions are met and 0 if not
*/

int isValidCode(int code)
{	
	int ans = 0;
	
	int duplicate = 0;
	const int TEN = 10;
	
	const int MIN = 1;
	const int MAX = 6;
	
	duplicate = code;
	
	firstDigit, secondDigit, thirdDigit, fourthDigit = 0;
	
	// here i'm saving each of the four digits into variables, so we can check conditions with them later
	
	fourthDigit = duplicate % TEN;
	duplicate /= TEN;
	thirdDigit = duplicate % TEN;
	duplicate /= TEN;
	secondDigit = duplicate % TEN;
	duplicate /= TEN;
	firstDigit = duplicate % TEN;
	duplicate /= TEN;
	
	if ((firstDigit >= MIN && firstDigit <= MAX) && (secondDigit >= MIN && secondDigit <= MAX) && (thirdDigit >= MIN && thirdDigit <= MAX) && (fourthDigit >= MIN && fourthDigit <= MAX)) { // checks if all digits are in the range of 1 to 6
		if ((firstDigit != secondDigit) && (firstDigit != thirdDigit) && (firstDigit != fourthDigit)) { // one liner won't work for some reason, so i used nested ifs to check if each digit is equal to the others
			if ((secondDigit != firstDigit) && (secondDigit != thirdDigit) && (secondDigit != fourthDigit)) {
				if ((thirdDigit != firstDigit) && (thirdDigit != secondDigit) && (thirdDigit != fourthDigit)) {
					if ((fourthDigit != firstDigit) && (fourthDigit != secondDigit) && (fourthDigit != thirdDigit)) {
						ans = 1;
					}
				}
			}
		}
	}
	
	return ans;
}

/**
This function is the gist of the code - the actual gameplay. It gets all the gameplay related inputs from the user, and also uses other functions, depending on the situation.
input: attempts - the number of attempts the user chose to have
output: none
*/

void play(int attempts) {
	int codeAsCharOne, codeAsCharTwo, codeAsCharThree, codeAsCharFour = 0;
	
	int firstInputDigit, secondInputDigit, thirdInputDigit, fourthInputDigit = 0;
	int flag1, flag2, flag3, flag4 = 0;
	
	int hits, misses = 0;
	int attemptCount = 0;
	
	int againFlag = 0;
	
	while (againFlag != ONE) {
		hits = 0;
		misses = 0;
		
		printf("\nWrite your guess (digits are only 1-6, no ENTER needed)\n");
		
		if (crazyFlag == ONE) {
			printf("CRAZY MODE!\n\n");
		}
		
		else {
			printf("%d guesses left\n\n", attempts);
		}
		
		firstInputDigit = getch();
		flag1 = checkInput(firstInputDigit);
		secondInputDigit = getch();
		flag2 = checkInput(secondInputDigit);
		thirdInputDigit = getch();
		flag3 = checkInput(thirdInputDigit);
		fourthInputDigit = getch();
		flag4 = checkInput(fourthInputDigit);
		
		while (flag1 == ZERO || flag2 == ZERO || flag3 == ZERO || flag4 == ZERO) {
			printf("\n\nOnly the digits 1-6 are allowed inside your guess... Try again!\n");
			printf("\nWrite your guess (digits are only 1-6, no ENTER needed)\n");
			
			if (crazyFlag == ONE) {
				printf("CRAZY MODE!\n\n");
			}
		
			else {
			printf("%d guesses left\n\n", attempts);
			}
			
			firstInputDigit = getch();
			flag1 = checkInput(firstInputDigit);
			secondInputDigit = getch();
			flag2 = checkInput(secondInputDigit);
			thirdInputDigit = getch();
			flag3 = checkInput(thirdInputDigit);
			fourthInputDigit = getch();
			flag4 = checkInput(fourthInputDigit);
		}

		attempts--;
		attemptCount++;
		
		// say the user inputs 1234 - it will be 49505152 in ascii, so here i'm converting the digits of the code to their corresponding ascii values
		
		codeAsCharOne = firstDigit + CONVERT_TO_ASCII;
		codeAsCharTwo = secondDigit + CONVERT_TO_ASCII;
		codeAsCharThree = thirdDigit + CONVERT_TO_ASCII;
		codeAsCharFour = fourthDigit + CONVERT_TO_ASCII;
		
		// i chose not to convert this section into a function because i thought it might cause me more problems in the future
		
		if (firstInputDigit == codeAsCharOne) {
			hits++;
		}
		
		else if (firstInputDigit == codeAsCharTwo || firstInputDigit == codeAsCharThree || firstInputDigit == codeAsCharFour) {
			misses++;
		}
		
		if (secondInputDigit == codeAsCharTwo) {
			hits++;
		}
		
		else if (secondInputDigit == codeAsCharOne || secondInputDigit == codeAsCharThree || secondInputDigit == codeAsCharFour) {
			misses++;
		}
		
		if (thirdInputDigit == codeAsCharThree) {
			hits++;
		}
		
		else if (thirdInputDigit == codeAsCharOne || thirdInputDigit == codeAsCharTwo || thirdInputDigit == codeAsCharFour) {
			misses++;
		}
		
		if (fourthInputDigit == codeAsCharFour) {
			hits++;
		}
		
		else if (fourthInputDigit == codeAsCharOne || fourthInputDigit == codeAsCharTwo || fourthInputDigit == codeAsCharThree) {
			misses++;
		}
		
		if (hits == WIN) {
			againFlag = win(attemptCount);
		}
		
		if (attempts == ZERO && againFlag != ONE) {
			againFlag = lose(hits, misses);
		}
		
		if (againFlag != ONE && hits != WIN && attempts != ZERO) {
			printf("\n\nYou got      %d HITS      %d MISSES\n", hits, misses);
		}
	}
}

/**
This function gets each digit of the number the user gave, and checks if it's in the range of 1 to 6
input: digit - one of the digits of the number the user gave as an input
output: flag, an integer that is 1 if the conditions are met and 0 if not
*/

int checkInput(int digit) {
	int flag = 0;
	
	const int MIN = 49;
	const int MAX = 54;
	
	if (digit >= MIN && digit <= MAX) {
		flag = 1;
	}
	
	putch(digit);
	
	return flag;
}

/**
This function tells the user he lost and gives him the option to quit playing or try again.
input: hits - the last number of hits the user got, misses - the last number of misses the user got
output: flag, an integer that is used to determine whether to quit playing or try again
*/

int lose(int hits, int misses) {
	int flag = 0;
	
	char playAgain = ' ';
	
	printf("\n\nYou got      %d HITS      %d MISSES\n", hits, misses);
	
	printf("\nOh no! Pancratius won and bought all of Hannuka's gifts.\nNothing left for you...\n\nThe secret passcode was %d\n\n", code);
			
	printf("Would you like to play again? (y/n): ");
			
	playAgain = getch();
	
	if (playAgain == CONTINUE) {
		putch(playAgain);
				
		printf("\n\n");		
		
		flag = 1; // having flag be 0 here in both the functions would cause a very very strange bug where inputing y then n won't end the program, this is the only fix i managed to think of. this is also used in the win() function
		main();
	}
			
	if (playAgain == STOP) {
		putch(playAgain);
				
		printf("\n\nGoodbye!\n");
		flag = 1;
	}
	
	if (playAgain != CONTINUE && playAgain != STOP) {
		putch(playAgain);
		
		while (playAgain != CONTINUE && playAgain != STOP) {
			printf("\n\nError! Please enter a valid option. So, would you like to play again? (y/n): ");
					
			playAgain = getch();
			
			putch(playAgain);
			
			if (playAgain == CONTINUE) {
				printf("\n\n");
				
				flag = 1;
				main();
			}
			
			if (playAgain == STOP) {
				printf("\n\nGoodbye!\n");
				flag = 1;
			}
		}
	}
	
	return flag;
}

/**
This function tells the user he won and gives him the option to quit playing or try again.
input: attemptCount - the number of attempts it took the user to guess correctly
output: flag, an integer that is used to determine whether to quit playing or try again
*/

int win(int attemptCount) {
	int flag = 0;
	
	char playAgain = ' ';
	
	printf("\n\nYou got      4 HITS      YOU WON!\n\n"); // printing 4 instead of using %d saves the usage of one more parameter
	printf("It only took you %d guesses, you are a professional code breaker!\n\n", attemptCount);
	
	printf("Would you like to play again? (y/n): ");
	
	playAgain = getch();
	
	if (playAgain == CONTINUE) {
		putch(playAgain);
				
		printf("\n\n");		
		
		flag = 1;
		main();
	}
			
	if (playAgain == STOP) {
		putch(playAgain);
				
		printf("\n\nGoodbye!\n");
		flag = 1;
	}
	
	if (playAgain != CONTINUE && playAgain != STOP) {
		putch(playAgain);
		
		while (playAgain != CONTINUE && playAgain != STOP) {
			printf("\n\nError! Please enter a valid option. So, would you like to play again? (y/n): ");
					
			playAgain = getch();
			
			putch(playAgain);
			
			if (playAgain == CONTINUE) {
				printf("\n\n");
				
				flag = 1;
				main();
			}
			
			if (playAgain == STOP) {
				printf("\n\nGoodbye!\n");
				flag = 1;
			}
		}
	}
	
	return flag;
}
