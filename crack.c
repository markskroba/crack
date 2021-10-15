#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>

/*
 * Checks all passwords with length of keysize to hash, returns the password if found, if not returns NULL
 */
char* guessPassword(int keysize, char* hash, char alphabet[]) {
    printf("guessPassword called for %d keysize and hash %s\n", keysize, hash);
    


    // creating an array of ints that corresponds to the letter number in the alphabet
    char password[keysize + 1];

    // filling with a's
    for (int i = 0; i < keysize; i++) {
        password[i] = 'a';
    }
    password[keysize] = '\0';

    for (int i = 1; i < keysize; i++) {

        // filling with a's
        for (int filling_i = 0; filling_i < keysize; filling_i++) {
            password[filling_i] = 'a';
        }
        password[keysize] = '\0';

        
        for (int j = 0; j < 26; j++) {
            password[i] = alphabet[j];
            printf("'%s'\n", password);

            
        }

    }

    printf("'%s'\n", password);
    return NULL;    
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Usage: crack <threads> <keysize> <target>\n");
        exit(-1);
    }
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // Handling input
    int threads = strtol(argv[1], NULL, 10);
    int keysize = strtol(argv[2], NULL, 10);
    char* target = argv[3];

    guessPassword(keysize, target, alphabet);

    return 0;
}