#ifndef h_AES
#define h_AES

#define SIZE 4
#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))

unsigned char state[SIZE][SIZE] = {
    {0x32, 0x88, 0x31, 0xE0},
    {0x43, 0x5A, 0x31, 0x37},
    {0xF6, 0x30, 0x98, 0x07},
    {0xA8, 0x8D, 0xA2, 0x34}
};

unsigned char key[SIZE][SIZE] = {
    {0x2B, 0x28, 0xAB, 0x09},
    {0x7E, 0xAE, 0xF7, 0xCF},
    {0x15, 0xD2, 0x15, 0x4F},
    {0x16, 0xA6, 0x88, 0x3C}
};

unsigned char C[SIZE][SIZE] = {
  {'02', '03', '01', '01'},
  {'01', '02', '03', '01'},
  {'01', '01', '02', '03'},
  {'03', '01', '01', '02'}
}

void add_round_key();
void subBytes();
void print_matrix(unsigned char M[SIZE][SIZE]);
// By: https://en.wikipedia.org/wiki/Rijndael_S-box
void initialize_aes_sbox(uint8_t sbox[256]);
void shiftRows();
void mixColumns();

#endif