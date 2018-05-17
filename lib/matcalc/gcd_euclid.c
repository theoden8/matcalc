#include <stdio.h>

#include "gcd_euclid.h"

bool calc_gcd_euclid(const mpz_t a_, const mpz_t b_, mpz_visitor visitor_func) {
	mpz_t a, b;
	mpz_inits(a, b, NULL);
	mpz_set(a, a_);
	mpz_set(b, b_);
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
