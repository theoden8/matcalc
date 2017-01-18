#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <gmp.h>


// nth euclid number is a product of first n primes + 1
// I will calculate that using eratosthene sieve iterator, which will iterate a
// sieve of upper bound defined according to prime number theorem.

#include "erat_sieve.h"
#include "visitor.h"

mpz_t euclid;
long Q;
mpz_visitor *euc_visitor_func = &mpz_printer;

void euclid_iter_func(uint N) {
	if(Q <= 0) {
		return;
	}
	--Q;
	mpz_mul_ui(euclid, euclid, N);
	mpz_add_ui(euclid, euclid, 1);
	/* printf("real bound... %u\n", N); */
	euc_visitor_func(&euclid);
	mpz_sub_ui(euclid, euclid, 1);
}

// using prime number theorem. is a dirty hack, but I like it.
uint n_primes_upper(uint n) {
	return ((double)n) * (log(n) + 1);
}

void visit(uint x, mpz_visitor visitor_func) {
	mpz_t res;
	mpz_init(res);
	mpz_set_si(res, x);
	visitor_func(&res);
	mpz_clear(res);
}

void calc_euclid(uint q, mpz_visitor visitor_func) {
	if(q == 0) {
		return;
	} else if(q == 1) {
		visit(3, visitor_func);
		return;
	}
	mpz_inits(euclid, NULL);
	visit(3, visitor_func);
	visit(7, visitor_func);
	q -= 2;
	mpz_set_si(euclid, 6);
	/* printf("upper bound %u\n", n_primes_upper(Q + 2)); */
	iterate_esieve(n_primes_upper(q + 2), euclid_iter_func);
	mpz_clears(euclid, NULL);
}

main(const argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	Q = atol(argv[1]);

	if(Q < 0)
		return EXIT_FAILURE;
	calc_euclid(Q, euc_visitor_func);
}
