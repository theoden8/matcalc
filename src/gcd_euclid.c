#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gmp.h>

#include "visitor.h"

bool calc_gcd_euclid(const char *left, const char *right, mpz_visitor visitor_func) {
	mpz_t a, b;
	mpz_inits(a, b, NULL);
	mpz_set_str(a, left, 10);
	mpz_set_str(b, right, 10);
	if(mpz_cmp_si(a, 0) < 0 || mpz_cmp_si(b, 0) < 0) {
		fputs("error: please, pick non-negative integers", stderr);
		return false;
	}
	while(mpz_cmp_si(a, 0) != 0 && mpz_cmp_si(b, 0) != 0) {
		if(mpz_cmp(a, b) > 0)
			mpz_fdiv_r(a, a, b);
		else if(mpz_cmp(a, b) < 0)
			mpz_fdiv_r(b, b, a);
		else break;
	}
	if(mpz_cmp_si(a, 0) == 0)
		mpz_set(a, b);
	visitor_func(&a);
	mpz_clears(a, b, NULL);
	return true;
}

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	if(!calc_gcd_euclid(
		argv[1], argv[2],
		mpz_printer)
	)
	{
		return EXIT_FAILURE;
	}
}
