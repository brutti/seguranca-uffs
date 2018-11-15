#ifndef CESAR_H
#define CESAR_H

#define MAX 1123
#define NSHIFT 3
#define ENCODE 1
#define DECODE 0

int getShift(char c);
char *caeser_cipher(char *plain_text, int operation);

#endif
