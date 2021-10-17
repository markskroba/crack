#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

void guessPassword(char password[], int keysize, int current_i, char* target, char salt[]) {

	if (current_i == keysize) {
		char* encrypted_password = crypt(password, salt);
		if (strcmp(target, encrypted_password) == 0) {
			printf("%s\n", password);
			exit(0);
		}
		return;
	}

	for (int i = 0; i < 26; i++) {
		password[current_i] = alphabet[i];
		guessPassword(password, keysize, current_i + 1, target, salt);
	}

}

int main(int argc, char* argv[]) {

	int keysize = strtol(argv[1], NULL, 10);
	char* target = argv[2];

	char salt[3];
	strncpy(salt, target, 2);

	for (int i = 1; i <= keysize; i++) {
		char password[i];

		guessPassword(password, i, 0, target, salt);
	}
	return 0;

}