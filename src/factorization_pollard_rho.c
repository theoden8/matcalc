#include <stdio.h>
#include <stdlib.h>

#include <matcalc/factorization_pollard_rho.h>
#include <matcalc/visitor.h>

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	mpz_t n;
	mpz_init_set_str(n, argv[1], 10);
	if(mpz_cmp_si(n, 0) < 0)
		return EXIT_FAILURE;
	calc_prime_factors_pollard_rho(n, mpz_printer);
	mpz_clear(n);
}
