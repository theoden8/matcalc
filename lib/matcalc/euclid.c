#include "euclid.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

static mpz_t n;
static long Q;
static mpz_visitor *euclid_visitor = &mpz_printer;

static bool euclid_iter_func(uint p) {
	if(Q <= 0)return false;
	--Q;
	mpz_mul_ui(n, n, p);
	mpz_add_ui(n, n, 1);
	/* printf("real bound... %u\n", N); */
	euclid_visitor(&n);
	mpz_sub_ui(n, n, 1);
	return true;
}

// using prime number theorem. is a dirty hack, but I like it.
static uint n_primes_upper(uint n) {
	return ((double)n) * (log(n) + 1);
}

static void visit(uint x, mpz_visitor visitor_func) {
	mpz_t res;
	mpz_init(res);
	mpz_set_si(res, x);
	visitor_func(&res);
	mpz_clear(res);
}

void calc_euclid(uint q, mpz_visitor visitor_func) {
	Q = q;
	if(q == 0) {
		return;
	} else if(q == 1) {
		visit(3, visitor_func);
		return;
	}
	mpz_inits(n, NULL);
	mpz_set_si(n, 1);
	/* printf("upper bound %u\n", n_primes_upper(Q + 2)); */
	esieve_t *e = get_esieve(n_primes_upper(Q));
	euclid_visitor = visitor_func;
	iter_esieve(e, euclid_iter_func);
	mpz_clears(n, NULL);
}
