#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

// nth euclid number is a product of first n primes + 1
// We will calculate that using eratosthene sieve iterator, which will iterate a
// sieve of upper bound defined according to prime number theorem.

#include <matcalc/euclid.h>

main(const argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	long Q = atol(argv[1]);

	if(Q < 0)
		return EXIT_FAILURE;
	calc_euclid(Q, mpz_printer);
  get_esieve(E_UNDEFINED);
}
