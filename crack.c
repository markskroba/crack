#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int thread_counter = 0;

struct data {
	struct crypt_data crypt_data;
	char* target;
	char* salt;
	int keysize;
	int from_i;
	int to_i;
};	

void guessPasswordForLetter(char password[], int keysize, int current_i, char* target, char salt[], int first_letter_index, struct crypt_data *crypt_data) {

	if (current_i == keysize) {
		// printf("%s\n", password);
	
		crypt_data->output;
		crypt_data->initialized = 0;

		char* encrypted_password = crypt_r(password, salt, crypt_data);
		if (strcmp(target, crypt_data->output) == 0) {
			printf("%s\n", password);
			exit(0);
		}
		return;
	}
	if (current_i == 0) {

		password[0] = alphabet[first_letter_index];
		guessPasswordForLetter(password, keysize, current_i + 1, target, salt, first_letter_index, crypt_data);

	} else {

		for (int i = 0; i < 26; i++) {
			password[current_i] = alphabet[i];
			guessPasswordForLetter(password, keysize, current_i + 1, target, salt, first_letter_index, crypt_data);
		}

	}
}

void* thread_entry(void* args) {
	struct data* argptr = args;

	for (int i = argptr->from_i; i < argptr->to_i; i++) {
		for (int length = 1; length <= argptr->keysize; length++) {
			char password[length];
			// pthread_mutex_lock(&mutex);
			guessPasswordForLetter(password, length, 0, argptr->target, argptr->salt, i, &argptr->crypt_data);
			// pthread_mutex_unlock(&mutex);
		}
	}

	return NULL;
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

	// Threading code

	// Calculating for how many letters each thread will guess passwords
	int iterations;
	int remainer;
	if (thread_count > 26) {
		iterations = 1;
		remainer = 0;
	} else {
		iterations = 26 / thread_count;
		remainer = 26 % thread_count;
	}

	struct data data[thread_count];
	int from_i = 0;
	int to_i = 0;

	pthread_t tid[thread_count];
	for (int i = 0; i < thread_count; i++) {
		from_i = to_i;
		to_i += iterations;
		if (i+1 == thread_count) {
			to_i += remainer;
		}

		data[i].from_i = from_i;
		data[i].to_i = to_i;
		data[i].keysize = keysize;
		data[i].target = target;
		data[i].salt = salt;

		int retval = pthread_create(&tid[i], NULL, thread_entry, &data[i]);
	}

	for (int j = 0; j < thread_count; j++) {
		pthread_join(tid[j], NULL);
	}
	return 0;

}