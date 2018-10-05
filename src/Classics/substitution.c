/*
 * Universidade Federal da Fronteira Sul
 * Ciência da Computação - SAS 2018.II
 * Acadêmico: Nicholas Sangoi Brutti (1421101033)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1123
#define ALPHABET_LEN 26
#define GETSHIFT(c) (islower(c) ? ('a') : ('A'))

char *buildAlphabet(char key[]) {
    int i;
    char *alphabet = (char *) calloc(ALPHABET_LEN, sizeof(char)), j = 97;
    for(int i = 0; i < strlen(key); i++) key[i] = tolower(key[i]);
    strcpy(alphabet, key);
    for (i = strlen(key); i < ALPHABET_LEN; i++) {
        while(strchr(alphabet, j)) j++;
        alphabet[i] = j++;
    }
    return alphabet;
}

char *encode(char *plain_text, char *alphabet) {
    char *cipher_text = (char *) calloc(strlen(plain_text) + 1, sizeof(char));
    int i;
    for (i = 0; plain_text[i] != '\0'; i++) {
        if(isalpha(plain_text[i])) {
            cipher_text[i] = toupper(alphabet[plain_text[i] % GETSHIFT(plain_text[i])]);
        } else cipher_text[i] = plain_text[i];
    }
    cipher_text[i] = '\0';
    return cipher_text;
}

char *decode(char *cipher_text, char *alphabet) {
    char *text = (char *) calloc(strlen(cipher_text) + 1, sizeof(char));
    int i, j;
    for (i = 0; cipher_text[i] != '\0'; i++) {
        if(!isalpha(cipher_text[i])) text[i] = cipher_text[i];
        else {
            int c = tolower(cipher_text[i]);
            for (j = 0; j < ALPHABET_LEN && alphabet[j] != c; j++);
            text[i] = j + 97;
        }
    }
    text[i] = '\0';
    return text;
}

int main(void) {
    char plain_text[MAX], key[MAX], *cipher_text = NULL, *decrypted_text = NULL, *alphabet = NULL;

    printf("+---------------------------------------------------+\n");
    printf("|\t\t Substitution Cipher\t\t    |\n");
    printf("+---------------------------------------------------+\n");

    printf("Digite a chave: ");
    fgets(key, MAX, stdin);
    key[strlen(key) - 1] = '\0';
    printf("Digite a mensagem: ");
    fgets(plain_text, MAX, stdin);
    plain_text[strlen(plain_text) - 1] = '\0';

    alphabet = buildAlphabet(key);
    cipher_text = encode(plain_text, alphabet);
    decrypted_text = decode(cipher_text, alphabet);

    printf("OUTPUT: \n");
    printf("Criptografado: %s\n", cipher_text);
    printf("Descriptografado: %s\n", decrypted_text);

    free(decrypted_text);
    free(cipher_text);
    free(alphabet);
    return 0;
}