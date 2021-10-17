#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>

// RECURSIVE
void guessPassword(char alphabet[], char password[], int keysize) {

	if (keysize == 0) {
		printf("%s\n", password);
		// printf("\n");
		return;
	}

	for (int i = 0; i < 26; i++) {
		// printf("Password: '%s', adding '%c' to it", password, alphabet[i]);

		password[keysize - 1] = alphabet[i];
		guessPassword(alphabet, password, keysize - 1);
	}

}

int main(int argc, char* argv[]) {

	char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int keysize = strtol(argv[1], NULL, 10);

	char password[keysize];
	for (int i = 0; i < keysize; i++) {
		password[i] = 'a';
	}
	guessPassword(alphabet, password, keysize);

	return 0;

}