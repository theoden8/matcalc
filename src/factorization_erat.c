#include <stdio.h>

#include <matcalc/factorization_erat.h>

main(int argc, char *argv[]) {
	if(argc != 2) {
		fputs("error: invalid number of arguments", stderr);
		return EXIT_FAILURE;
	}
	mpz_t n;
	mpz_init_set_str(n, argv[1], 10);
	calc_prime_factors_erat(n, prime_printer);
	get_esieve(E_UNDEFINED);
	mpz_clear(n);
}
