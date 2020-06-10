#include <stdbool.h>

#include "nth_derangements.h"

// derangement is a permutation of a sequence (1..n) s.t. pmt(i) != i for i in [1..n]
//
// the number of derangements can be computed in recursively as:
//	d(n) = (n - 1) * (d(n - 1) + d(n - 2)) for n >= 3, otherwise {0, 1, 2}
//	d(n) = n*d(n - 1) + (-1)^n
// and iteratively as:
//	d(n) = sum( (-1)^k * (n!/k!) | k <- 0..n ) =
//		= n! * sum( (-1)^k / k! | k <- 0..n )

#include <stdio.h>
static void nth_derangements(mpz_t d_n, long n) {
	mpz_t n_fac;
	mpz_inits(n_fac, NULL);

	mpz_set_si(d_n, 0);
	mpz_set_si(n_fac, 1);
	for(long i = n; i >= 2; --i) {
		((i & 1) ? mpz_sub : mpz_add)(d_n, d_n, n_fac);
		if(i != 2)
			mpz_mul_ui(n_fac, n_fac, i);
	}
	mpz_clears(n_fac, NULL);
}

void calc_nth_derangement(long n, mpz_visitor visitor_func) {
	mpz_t d_n;
	mpz_init(d_n);

	nth_derangements(d_n, n);
	visitor_func(&d_n);

	mpz_clear(d_n);
}
