// Baseado em: https://medium.com/@tarcisiomarinho/algoritmo-de-criptografia-assim%C3%A9trica-rsa-c6254a3c7042

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void crivoDeEratostenes(int MAX) {
    long long int raiz = floor(sqrt(MAX));
    long long int *primos = (long long int *) calloc(MAX, sizeof(long long int));
    int i, j;

    if (!primos) {
        printf("Memória indisponível.. \n");
        return;
    }

    for (i = 2; i <= MAX; i++)
        primos[i] = i;

    for (i = 2; i <= raiz; i++) {
        if(primos[i] == i) {
            for (j = i + i; j <= MAX; j += i) {
                primos[j] = 0; // Remove da lista
            }
        }
    }

    for (i = 0; i < MAX; i++)
        printf("%lld ", primos[i]);

}

long long int funcaoTotienteEuler(long long int P, long long int Q) {
    return (P - 1) * (Q - 1);
}

int main(void) {
    long long int P, Q, N, E;

    printf("Digite dois números primos (P e Q): ");
    scanf("%lld %lld", &P, &Q);

    N = P * Q;
    E = funcaoTotienteEuler(P, Q);
    crivoDeEratostenes(E);

    return 0;
}