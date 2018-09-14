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

char cipher_text[MAX],  decrypted_text[MAX];

// Faz o deslocamento na tabela ASCII [97 -> 'a' & 65 -> 'A']
int getShift(char c) {
    return c - (islower(c) ? 97 : 65);
}

char *encode(char *plain_text, char *key) {
	char *cipher_text = (char *) calloc(strlen(plain_text), sizeof(char));
    int key_length = strlen(key);
    int i, j = 0;
    for (i = 0; plain_text[i] != '\0'; i++) {
        int c = getShift(plain_text[i]);
        cipher_text[i] = (c + (getShift(key[j % key_length]))) % 26;
        cipher_text[i] += 'a';
        if(plain_text[i] == ' ') cipher_text[i] = ' ';
        else j++;
    }
    cipher_text[++i] = '\0';
    return cipher_text;
}

char *decode(char *cipher_text, char *key) {
    int key_length = strlen(key);
    char *text = (char *) calloc(strlen(cipher_text), sizeof(char));
    int i, j = 0;

    for (i = 0; cipher_text[i] != '\0'; i++) {
        int c = getShift(cipher_text[i]);
        text[i] = (c - (getShift(key[j % key_length])) + 26) % 26;
        text[i] += 'a';
        if(cipher_text[i] == ' ') text[i] = ' ';
        else j++;
    }
    text[++i] = '\0';
    return text;
}

int main(void) {
	char plain_text[MAX], key[MAX], *cipher_text = NULL, *text = NULL;

    printf("+---------------------------------------------------+\n");
    printf("|\t\t    Vigenere Cipher\t\t    |\n");
    printf("+---------------------------------------------------+\n");

    printf("Digite a mensagem: ");
    fgets(plain_text, MAX, stdin);
    plain_text[strlen(plain_text) - 1] = '\0';

    printf("Digite a chave: ");
    fgets(key, MAX, stdin);
    key[strlen(key) - 1] = '\0';

    if(strchr(key, ' ')) {
        printf("A chave nao pode conter espacos.\n");
        return -1;
    }
    
    cipher_text = encode(plain_text, key);
    text = decode(cipher_text, key);

    printf("OUTPUT: \n");
    printf("Criptografado: %s\n", cipher_text);
    printf("Descriptografado: %s\n", text);

    return 0;
}
