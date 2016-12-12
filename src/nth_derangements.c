#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <gmp.h>

// derangement is a permutation of a sequence (1..n) s.t. pmt(i) != i for i in [1..n]
//
// the number of derangements can be computed in recursively as:
//	d(n) = (n - 1) * (d(n - 1) * d(n - 2)) for n >= 3, otherwise {0, 1, 2}
//	d(n) = n*d(n - 1) + (-1)^n
// and iteratively as:
//	d(n) = sum( (-1)^k * (n!/k!) | k <- 0..n )

void nth_derangements(mpz_t *d_n, long n) {
	mpz_t n_fac;
	mpz_inits(n_fac, NULL);

	mpz_set_si(*d_n, 0);
	mpz_fac_ui(n_fac, n);
	bool sgn = false;
	for(long i = 2; i <= n; ++i) {
		mpz_div_ui(n_fac, n_fac, i);
		(i & 1 ? mpz_sub : mpz_add)(*d_n, *d_n, n_fac);
	}

	mpz_clears(n_fac, NULL);
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const long N = atol(argv[1]);
	if(N < 1)
		return EXIT_FAILURE;
	mpz_t d_n;
	mpz_init(d_n);

	nth_derangements(&d_n, N);
	gmp_printf("%Zd\n", d_n);

	mpz_clear(d_n);
}
