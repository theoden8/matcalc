#include "factorization_pollard_rho.h"

static void p_rho_next_divisor(mpz_t n, mpz_visitor visitor_func) {
	mpz_t d, x, y, x_y, cycle_size;
	mpz_init(x_y);
	mpz_init_set_si(d, 1);
	mpz_init_set_si(x, 2);
	mpz_init_set_si(y, 2);
	mpz_init_set_si(cycle_size, 2);
	while(mpz_cmp_ui(d, 1) == 0) {
		for(long i = 1; mpz_cmp_ui(cycle_size, i) > 0 && mpz_cmp_si(d, 1) <= 0; ++i) {
			// x = (x * x) % n
			mpz_mul(x, x, x);
			mpz_add_ui(x, x, 1u);
			mpz_mod(x, x, n);
			// d = gcd(x - y, n)
			mpz_sub(x_y, x, y);
			mpz_gcd(d, x_y, n);
		}
		// cycle_size <<= 1
		mpz_mul_ui(cycle_size, cycle_size, 2);
		// y = x
		mpz_set(y, x);
	}
	mpz_div(n, n, d);
	mpz_t two;
	mpz_init_set_d(two, 2);
	while(mpz_even_p(d)) {
		visitor_func(&two);
		mpz_div_ui(d, d, 2);
	}
	mpz_clear(two);
	if(mpz_cmp_ui(d, 1) > 0) {
		visitor_func(&d);
	}
	mpz_clears(d, x, y, x_y, cycle_size, NULL);
}

void calc_prime_factors_pollard_rho(const mpz_t z, mpz_visitor visitor_func) {
	mpz_t n;
	mpz_inits(n, NULL);
	mpz_set(n, z);
	while(mpz_cmp_si(n, 1) != 0) {
		p_rho_next_divisor(n, visitor_func);
	}
	mpz_clears(n, NULL);
}
