#include "catalans.h"

// catalan numbers are cowpowers of combinatorics which stand for the total
// possible ways to make up a balanced sequence of range twice as big as the
// index of a catalan number itself
//
// recursively,
//  (1) c(n) = sum(c(i - 1) * c(n - i) | i <- [1..n]) : c(0) = 1
// iteratively,
//  (1) c(n) = c_nk(2n, n) * 1/(n + 1)
//  (2) c(n) = product( 2 * (2 * i - 1) / (i + 1) | i <- [1..n] )

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
