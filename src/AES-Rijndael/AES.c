#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "AES.h"

void add_round_key() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            state[i][j] ^= key[i][j];
}

void print_matrix(unsigned char M[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%04x ", M[i][j]);
        }
        printf("\n");
    }
}

void initialize_aes_sbox(uint8_t sbox[256]) {
    uint8_t p = 1, q = 1;
    
    /* loop invariant: p * q == 1 in the Galois field */
    do {
        /* multiply p by 3 */
        p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

        /* divide q by 3 (equals multiplication by 0xf6) */
        q ^= q << 1;
        q ^= q << 2;
        q ^= q << 4;
        q ^= q & 0x80 ? 0x09 : 0;

        /* compute the affine transformation */
        uint8_t xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);

        sbox[p] = xformed ^ 0x63;
    } while (p != 1);

    /* 0 is a special case since it has no inverse */
    sbox[0] = 0x63;
}

void subBytes(uint8_t sbox[256]) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            int index = state[i][j];
            state[i][j] = sbox[index];
        }
    }
}

char findValue(char bkp_line[SIZE]) {
    int i;

    for (i = 0; i < SIZE; i++) {
        if (bkp_line[i] != 'a') {
            char r = bkp_line[i];
            bkp_line[i] = 'a';
            return r;
        }
    }
    return 0;
}

void shiftRows() {
    char bkp_line[SIZE];
    int i, j, k;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < i; j++) {
            bkp_line[j] = state[i][j];
        }
        for (k = i; k < SIZE; k++) {
            char tmp = state[i][k];
            state[i][k - j] = tmp;
        }
        for (k = SIZE - i; k < SIZE; k++) {
            state[i][k] = findValue(bkp_line);
        }
    }
}

void mixColumns() {
    
}

int main(void) {
    int i;
    uint8_t sbox[256];

    add_round_key();
    print_matrix(state);
    initialize_aes_sbox(sbox);

    for (i = 0; i < 256; i++)
        printf("%x ", sbox[i]);

    subBytes(sbox);
    shiftRows();

    printf("\n");
    print_matrix(state);

    return 0;
}