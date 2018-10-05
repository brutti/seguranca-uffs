/*
 * Universidade Federal da Fronteira Sul
 * Ciência da Computação - SAS 2018.II
 * Acadêmico: Nicholas Sangoi Brutti (1421101033)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1123

char alfabeto[MAX], chave[MAX], texto[MAX], cp[MAX];
int lin, col;

int cmp(const void *a, const void *b) {
    int i = *(int *)a, j = *(int *)b;
    return (chave[i] > chave[j]);
}

void printMatriz(char matriz[lin][col], int flag){
    int i, j;
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++)
            printf("%c", matriz[i][j]);
        if(flag) printf("\n");
    }
}

void criaMatriz(char matriz[lin][col]){
    int i, j, k = 0;
    int t;
    
    for (i = 0; i < lin && texto[k] != '\0'; i++) {
        for (j = 0; j < col && texto[k] != '\0'; j++) {
            matriz[i][j] = texto[k];
            k++;
            t = j;
        }
    }
    for (j = t; j < col; j++)
        matriz[lin - 1][j + 1] = 97;
}


void cript(char matriz[lin][col]){
    int i, j, contcp = 0;
    int index[col];
    for (i = 0; i < col; i++){
        index[i] = i;
    }
    qsort(index, col, sizeof(int), &cmp);
    for (i = 0; i < col; i++) {
        for (j = 0; j < lin; j++) {
            cp[contcp] = matriz[j][index[i]];
            contcp++;
        }
    }
    cp[contcp] = '\0';   
}

void descript(char dcp[lin][col]){
    int i, j, contcp = 0;
    int index[col];
    for (i = 0; i < col; i++) {
        index[i] = i;
    }
    qsort(index, col, sizeof(int), &cmp);
    for (i = 0; i < col; i++) {
        for (j = 0; j < lin; j++) {
            dcp[j][index[i]] = cp[contcp];
            contcp++;
        }
    }    
}


int main(){
    int T;

    printf("+---------------------------------------------------+\n");
    printf("|\t         Transposition Cipher\t            |\n");
    printf("+---------------------------------------------------+\n");

    printf("Digite a chave: ");
    fgets(chave, MAX, stdin);
    chave[strlen(chave) - 1] = '\0';
    
    printf("Digite a mensagem: ");
    fgets(texto, MAX, stdin);
    texto[strlen(texto)-1] = '\0';
    
    col = strlen(chave);
    T = strlen(texto) - 1;
    lin = ceil((double)T/(double)col);

    char matriz[lin][col];
    char dcp[lin][col];
    
    criaMatriz(matriz);
    //Criptografia
    cript(matriz);
    
    printf("OUTPUT: \n");
    printf("Criptografado: %s\n", cp);

    //Descriptografar
    descript(dcp);
    printf("Descriptografado: ");
    printMatriz(dcp,0);
    printf("\n");
        
    return 0;
}