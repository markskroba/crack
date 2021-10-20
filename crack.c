#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

void guessPasswordForLetter(char password[], int keysize, int current_i, char* target, char salt[], int first_letter_index) {
	/* 
	 * Guesses passwords for given first letter
	 */

	if (current_i == keysize) {
		printf("%s\n", password);
		char* encrypted_password = crypt(password, salt);
		if (strcmp(target, encrypted_password) == 0) {
			printf("%s\n", password);
			exit(0);
		}
		return;
	}
	if (current_i == 0) {

		password[0] = alphabet[first_letter_index];
		guessPasswordForLetter(password, keysize, current_i + 1, target, salt, first_letter_index);

	} else {

		for (int i = 0; i < 26; i++) {
			password[current_i] = alphabet[i];
			guessPasswordForLetter(password, keysize, current_i + 1, target, salt, first_letter_index);
		}

	}
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: crack <threads> <keysize> <target>\n");
		exit(-1);
	}

	int thread_count = strtol(argv[1], NULL, 10);
	int keysize = strtol(argv[2], NULL, 10);
	char* target = argv[3];

	if (keysize > 8) {
		printf("The maximum allowed keysize is 8\n");
		exit(-1);
	}

	char salt[3];
	strncpy(salt, target, 2);

	for (int i = 1; i <= keysize; i++) {
		char password[i];

		guessPasswordForLetter(password, i, 0, target, salt, 5);
	}
	return 0;

}