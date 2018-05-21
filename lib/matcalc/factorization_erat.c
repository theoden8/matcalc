#include "factorization_erat.h"

#include <stdlib.h>

static uint get_sieve_size(const mpz_t x) {
	mpz_t xsqrt;
	mpz_init(xsqrt);
	mpz_sqrt(xsqrt, x);
	const uint max_sieve = (uint)1e9;
	uint sieve_size = E_CURRENT;
	if(mpz_cmp_ui(xsqrt, max_sieve) > 0) {
		sieve_size = max_sieve;
	} else {
		mpz_export(&sieve_size, 0, -1, sizeof(sieve_size), 0, 0, xsqrt);
	}
	mpz_clear(xsqrt);
	return sieve_size;
}

static mpz_t z;

static prime_visitor *prime_factor_func = prime_printer;

static bool visit_prime(uint p) {
	if(mpz_cmp_ui(z, p * p) < 0)return false;
	while(mpz_divisible_ui_p(z, p)) {
		mpz_divexact_ui(z, z, p);
		prime_factor_func(p);
	}
	return true;
}

void calc_prime_factors_erat(const mpz_t n, prime_visitor visitor_func) {
	mpz_init(z);
	mpz_set(z, n);
	prime_factor_func = visitor_func;

	uint max_sieve_size = get_sieve_size(n);
	/* printf("square root: %d\n", max_sieve_size); */

	esieve_t *e = get_esieve(max_sieve_size);

	iter_esieve(e, visit_prime);
	if(mpz_cmp_ui(z, 1) > 0) {
		uint last = 0;
		mpz_export(&last, 0, -1, sizeof(last), 0, 0, z);
		prime_factor_func(last);
	}

	mpz_clear(z);
}
