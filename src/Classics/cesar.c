/*
 * Universidade Federal da Fronteira Sul
 * Ciência da Computação - SAS 2018.II
 * Acadêmico: Nicholas Sangoi Brutti (1421101033)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cesar.h"

// Faz o deslocamento na tabela ASCII [97 -> 'a' & 65 -> 'A']
int getShift(char c) {
    return c - (islower(c) ? 97 : 65);
}

char *caeser_cipher(char *plain_text, int operation) {
    char *cipher_text = (char *) calloc(strlen(plain_text) + 1, sizeof(char));
    int i;

    for (i = 0; plain_text[i] != '\0'; i++) {
        int c = getShift(plain_text[i]);

        if(operation == ENCODE) {
            cipher_text[i] = (c + NSHIFT) % 26 + 'a';
            if(plain_text[i] == ' ') cipher_text[i] = '#';
        }
        else if(operation == DECODE) {
            cipher_text[i] = (c - NSHIFT) < 0 ? (123 + (c - NSHIFT)) :
                                                (c - NSHIFT + 'a');
            if(plain_text[i] == '#') cipher_text[i] = ' ';
        }

        if(!isalpha(plain_text[i])) cipher_text[i] = plain_text[i];
    }
    cipher_text[i] = '\0';
    return cipher_text;
}
