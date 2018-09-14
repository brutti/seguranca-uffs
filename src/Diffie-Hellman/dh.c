/*
 * Universidade Federal da Fronteira Sul
 * Ciência da Computação - SAS 2018.II
 * Acadêmico: Nicholas Sangoi Brutti (1421101033)
 */

#include <stdio.h>
#include <stdlib.h>

long long int expbinmod(long long a, long long x, long long m) {
	long long int b;
	if (x == 0) return 1;
	if (x & 1) return a * expbinmod(a, x - 1, m) % m;
	b = expbinmod(a, x >> 1, m);
	return b * b % m;
}

int main(void) {
	long long int p, g, cA, cB, rA, rB, pkey_a, pkey_b;

	printf("Digite o valor de p (primo) e g (gerador): ");
	scanf("%lld %lld", &p, &g);

	printf("Digite o valor de cA (Confidencial A) e cB (Confidencial B): ");
	scanf("%lld %lld", &cA, &cB);

	rA = expbinmod(g, cA, p);
	rB = expbinmod(g, cB, p);

	pkey_a = expbinmod(rB, cA, p);
	pkey_b = expbinmod(rA, cB, p);

	printf("Chave de A = %lld\nChave de B = %lld\n", pkey_a, pkey_b);
	return 0;
}
