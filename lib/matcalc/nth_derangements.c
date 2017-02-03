#include <stdbool.h>

#include "nth_derangements.h"

static void nth_derangements(mpz_t *d_n, long n) {
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

void calc_nth_derangement(long n, mpz_visitor visitor_func) {
	mpz_t d_n;
	mpz_init(d_n);

	nth_derangements(&d_n, n);
	visitor_func(&d_n);

	mpz_clear(d_n);
}
