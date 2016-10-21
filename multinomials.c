#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <gmp.h>

// polynomial coefficients.
// the file is called multinomials.c because polynimials would mean that
// x-power-ish finite series, and the polynomial-coefficients would be too long
// to write, cant be bothered.
//
// polynomial coefficients are the ones obtained when expanding a (sum of m
// variables) to the n.
//
// for more relevant information about that thing, read the code

mpz_t n_fac;

typedef struct _poly_args {
	int n, *k, m;
	mpz_t *k_facs;
} poly_args;


void print_coeff(poly_args pa) {
	mpz_t coeff;
	mpz_init(coeff);

	mpz_set(coeff, n_fac);

	for(int i = 0; i < pa.m; ++i) {
		mpz_fdiv_q(coeff, coeff, pa.k_facs[pa.k[i]]);
	}

	gmp_printf("%Zd ", coeff);

	mpz_clear(coeff);
}

// this is, by the way, natural number partition for n*n. However, as opposed to
// n_partition, it needs to output each result.
void recurse_search(poly_args pa, int smaller_n, int idx) {
	if(idx == pa.m - 1) {
		pa.k[idx] = smaller_n;
		print_coeff(pa);
		/* for(int i = 0; i < pa.m; ++i) */
		/* 	gmp_printf("%d ", pa.k[i]); */
		gmp_printf("\n");
		return;
	}
	else {
		for(int i = 0; i <= smaller_n; ++i) {
			pa.k[idx] = i;
			recurse_search(pa, smaller_n - i, idx + 1);
		}
	}
}

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	int
		m = atoi(argv[1]), // number of summons
		n = atoi(argv[2]), // power
		k[m];

	mpz_t k_facs[n + 1];
	mpz_init(n_fac);
	for(int i = 0; i < n + 1; ++i) {
		mpz_init(k_facs[i]);
		mpz_fac_ui(k_facs[i], i);
	}
	mpz_fac_ui(n_fac, n);

	memset(k, 0, m * sizeof(int));
	poly_args pargs = { n, k, m, k_facs };
	recurse_search(pargs, n, 0);

	for(int i = 0; i < n + 1; ++i) {
		mpz_clear(k_facs[i]);
	}
	mpz_clear(n_fac);
}
