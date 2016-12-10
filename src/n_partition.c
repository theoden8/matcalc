#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <gmp.h>

typedef long long llong;

// calculates the number of partions of a given natural number
//
// let n be the number we want to count partitions for.
//
// let M = (1 + x + x^2 + ...) * (1 + (x^2) + (x^2)^2 + ...) * ... * (1 + (x^n) + (x^n)^2 + ...)
//
// We can notice that coeff(expand(M), x^n) = p(n) = number of partitions of n.
//
// Simplify M:
//  M = 1 / ((1 + x) * (1 + x^2) * ... )
//
// Because we are interested in expanding denominator,
// M' = (1 + x) * (1 + x^2) * ... = product(k = 0, inf, 1 + x^k)
//
// Apply euler's pentagonal theorem:
// M' = product(k=0, inf, 1 + x^k) = sum(q=-inf, inf, (-1)^q * x * ((3*q^2 + q) / 2))
//
// p(n) = (-1)^(q + 1) * (p(n - (3q*q - q)/2) + p(n - (3*q*q + q)/2))
//        while (n - (3*q*q + q)/2 >= 0)
//
// We can calculate this using recursion. But wait! For p(n) we need to
// calculate p(n - 1) and p(n - 2) as the first two summons. This means, that
// we can compute this iteratively without having to calculate anything twice.


mpz_t *alloc_partition_ans(int n) {
	mpz_t *P = malloc(sizeof(mpz_t) * (n + 1));
	for(int i = 0; i <= n; ++i)
		mpz_init(P[i]);
	return P;
}

void clear_partition_ans(mpz_t *P, int n) {
	for(int i = 0; i <= n; ++i)
		mpz_clear(P[i]);
	free(P);
}


void partition(int n, mpz_t *P) {
	mpz_t term;
	mpz_inits(term, NULL);

	for(int i = 0; i <= n; ++i) {
		if(i == 0 || i == 1) {
			mpz_set_si(P[i], 1);
			continue;
		}
		char
			sign = 1;
		llong
			pent1 = 1, // (3q*q - q)/2
			pent2 = 2, // (3q*q + q)/2
			q = 0;
		mpz_set_si(P[i], 0);

		while(i - pent2 >= 0) {
			mpz_add(term, P[i - pent1], P[i - pent2]);
			mpz_mul_si(term, term, sign);
			mpz_add(P[i], P[i], term);
			++q;
			sign = -sign;
			pent1 += 3*q + 1;
			pent2 += 3*q + 2;
			assert(pent2 > 0);
		}
		if(i - pent1 >= 0) {
			mpz_mul_si(term, P[i - pent1], sign);
			mpz_add(P[i], P[i], term);
		}
	}

	mpz_clears(term, NULL);
}


// for no particular reason, I want this to be recursive
int find_max(int *arr, int len) {
	if(len == 0)
		return -1;
	if(len == 1)
		return *arr;
	const half = len >> 1;
	int l = find_max(arr, half),
			r = find_max(arr + half, half + (len & 1));
	return (l > r) ? l : r;
}

main(const argc, char *argv[]) {
	if(argc == 1)
		return EXIT_SUCCESS;

	int n[argc - 1];
	for(int i = 1; i < argc; ++i) {
		const tmp = atoi(argv[i]);
		assert(tmp >= 0);
		n[i - 1] = tmp;
	}
	int max = find_max(n, argc - 1);

	mpz_t *P = alloc_partition_ans(max);
	partition(max, P);
	for(int i = 1; i < argc; ++i) {
		gmp_printf("%Zd\n", P[n[i - 1]]);
	}
	clear_partition_ans(P, max);
}
