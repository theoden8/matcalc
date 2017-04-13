#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

void next_divisor(mpz_t n, mpz_t d) {
	mpz_t x, x_fixed, cycle_size;
	mpz_inits(x, x_fixed, cycle_size, NULL);
	mpz_set_si(x, 2);
	mpz_set_si(x_fixed, 2);
	mpz_set_si(cycle_size, 2);
	mpz_set_si(d, 1);
	while(mpz_cmp_si(d, 1) == 0) {
		for(long i = 1; mpz_cmp_ui(cycle_size, i) > 0 && mpz_cmp_si(d, 1) <= 0; ++i) {
			mpz_mul(x, x, x);
			mpz_add_ui(x, x, 1u);
			mpz_fdiv_r(x, x, n);
			mpz_sub(x, x, x_fixed);
			mpz_gcd(d, x, n);
			mpz_add(x, x, x_fixed);
		}
		mpz_mul_ui(cycle_size, cycle_size, 2);
		mpz_set(x_fixed, x);
	}
	mpz_div(n, n, d);
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	mpz_t n, d;
	mpz_inits(n, d, NULL);
	mpz_set_str(n, argv[1], 10);
	if(mpz_cmp_si(n, 0) < 0)
		return EXIT_FAILURE;
	while(mpz_cmp_si(n, 1) != 0) {
		next_divisor(n, d);
		gmp_printf("%Zd\n", d);
	}
	mpz_clears(n, d, NULL);
}
