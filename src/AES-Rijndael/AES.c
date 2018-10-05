#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "AES.h"

void addRoundKey() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            state[i][j] ^= key[i][j];
}

void printMatrix(unsigned char M[SIZE][SIZE]) {
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

void subBytes() {
    
}

int main(void) {
    uint8_t sbox[256];

    addRoundKey();
    printMatrix(state);
    initialize_aes_sbox(sbox);

    for(int i = 0; i < 256; i++) {
        printf("%04x ", sbox[i]);
    }

    return 0;
}