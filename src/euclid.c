#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <gmp.h>


// nth euclid number is a product of first n primes + 1
// I will calculate that using eratosthene sieve iterator, which will iterate a
// sieve of upper bound defined according to prime number theorem.

#include "erat_sieve.h"

mpz_t euclid;
long Q;

void euclid_iter_func(uint N) {
	if(Q <= 0) {
		return;
	}
	--Q;
	mpz_mul_ui(euclid, euclid, N);
	mpz_add_ui(euclid, euclid, 1);
	/* printf("real bound... %u\n", N); */
	gmp_printf("%Zd\n", euclid);
	mpz_sub_ui(euclid, euclid, 1);
}

// using prime number theorem. is a dirty hack, but I like it.
uint n_primes_upper(uint n) {
	return ((double)n) * (log(n) + 1);
}

main(const argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	Q = atol(argv[1]);

	if(Q < 0)
		return EXIT_FAILURE;
	else if(Q == 0)
		return EXIT_SUCCESS;
	else if(Q == 1) {
		printf("3\n");
		return EXIT_SUCCESS;
	}

	mpz_inits(euclid, NULL);

	printf("3\n7\n");
	Q -= 2;
	mpz_set_si(euclid, 6);
	/* printf("upper bound %u\n", n_primes_upper(Q + 2)); */
	iterate_esieve(n_primes_upper(Q + 2), euclid_iter_func);
	mpz_clears(euclid, NULL);
}
