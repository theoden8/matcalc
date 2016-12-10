#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

// this one should be raised for charity
// c[n] = 2n! / (n! * (n + 1)!)

void nth_catalan(mpz_t cat, unsigned n) {
	mpz_t n_fac;
	mpz_init(n_fac);
	mpz_fac_ui(cat, 2 * n);
	mpz_fac_ui(n_fac, n);
	mpz_pow_ui(n_fac, n_fac, 2);
	mpz_mul_ui(n_fac, n_fac, n + 1);
	mpz_fdiv_q(cat, cat, n_fac);
	mpz_clear(n_fac);
}

main(int argc, char *argv[]) {
	mpz_t cat;
	mpz_init(cat);
	for(int i = 1; i < argc; ++i) {
		nth_catalan(cat, atoi(argv[i]));
		gmp_printf("%Zd\n", cat);
	}
	mpz_clear(cat);
}
