#include "nth_catalan.h"

static void nth_catalan(mpz_t cat, unsigned n) {
	mpz_t n_fac;
	mpz_init(n_fac);
	mpz_fac_ui(cat, 2 * n);
	mpz_fac_ui(n_fac, n);
	mpz_pow_ui(n_fac, n_fac, 2);
	mpz_mul_ui(n_fac, n_fac, n + 1);
	mpz_fdiv_q(cat, cat, n_fac);
	mpz_clear(n_fac);
}

void calc_nth_catalan(size_t n, mpz_visitor visitor_func) {
	mpz_t cat;
	mpz_init(cat);
	nth_catalan(cat, n);
	visitor_func(cat);
	mpz_clear(cat);
}

