#include <assert.h>
#include <stdio.h>

#include "c_nk.h"

// binomial coefficients
// ( n )
// ( k )
//
// c_n^k = n!/(k!(n-k)!)
//
// pascals triangle:
// 1
// 1 1
// 1 2 1
// 1 3 3  1
// 1 4 6  4  1
// 1 5 10 10 5  1
// 1 6 15 20 15 6 1
// ...

static void binomial_u(size_t n, size_t k, mpz_t res) {
	assert(n >= 0 && k >= 0);
	mpz_bin_uiui(res, n, k);
}

static void binomial_s(long n, long k, mpz_t res) {
	if(n >= 0) {
		binomial_u(n, k, res);
	} else {
		binomial_u(-n + k - 1, k, res);
		if(k & 1) {
			mpz_mul_si(res, res, -1);
		}
	}
}

void calc_c_nk(long n, long k, mpz_visitor visitor_func) {
	mpz_t res;
	mpz_init(res);
	binomial_s(n, k, res);
	visitor_func(&res);
	mpz_clear(res);
}
