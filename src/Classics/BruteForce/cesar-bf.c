#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cesar.h"

#define ALPHABET_SIZE 26

void bruteForce(char *encrypted, char *expected) {
    int n_shifts = 0, i;
    char buffer[MAX];
    
    while(1) {
        for (i = 0; encrypted[i] != '\0'; i++)
            buffer[i] = encrypted[i] - n_shifts;
        buffer[i] = '\0';
        if (strcmp(buffer, expected) == 0) {
            printf("Cifra quebrada :)\n");
            printf("Após %d iterações a chave foi quebrada. O deslocamento usado para cifrar foi de: %d caracteres\n", i, n_shifts);
            return;
        }
        n_shifts++;
    }
}

int main(void) {
    char expected[] = "olocomeu";
    char *encrypted = caeser_cipher(expected, ENCODE);

    bruteForce(encrypted, expected);
    return 0;
}
