#include "catalans.h"

void calc_catalans(size_t n, mpz_visitor visitor_func) {
	mpz_t catalan;
	mpz_init(catalan);
	mpz_set_si(catalan, 1);

	visitor_func(&catalan);
	for(int i = 1; i < n; ++i) {
		mpz_mul_ui(catalan, catalan, 2*(2*i - 1));
		mpz_fdiv_q_ui(catalan, catalan, i + 1);
		visitor_func(&catalan);
	}
	mpz_clear(catalan);
}
