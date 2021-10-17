#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>

// RECURSIVE
void guessPassword(char alphabet[], char password[], int keysize, char* target, char salt[]) {

	if (keysize == 0) {
		char* encrypted_password = crypt(password, salt);
		if (strcmp(target, encrypted_password) == 0) {
			printf("%s\n", password);
			exit(0);
		}
		return;
	}

	for (int i = 0; i < 26; i++) {
		password[keysize - 1] = alphabet[i];
		guessPassword(alphabet, password, keysize - 1, target, salt);
	}

}

int main(int argc, char* argv[]) {

	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	int keysize = strtol(argv[1], NULL, 10);
	char* target = argv[2];

	char password[keysize];
	for (int i = 0; i < keysize; i++) {
		password[i] = 'a';
	}

	char salt[3];
	strncpy(salt, target, 2);

	guessPassword(alphabet, password, keysize, target, salt);

	return 0;

}