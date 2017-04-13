#include <stdbool.h>

#include "figurate.h"

void calc_figurate(long k, long n, mpz_visitor visitor_func) {
	mpz_t f, s;
	mpz_inits(f, s, NULL);
	mpz_set_si(f, 0);
	const long BREAK = (LONG_MAX - 1) / (k - 2);
	bool over = false;
	for(long i = 0; i < n; ++i) {
		if(!over) {
			long step = 1 + i * (k - 2);
			if((i + 1) < BREAK) {
				mpz_add_ui(f, f, step);
			} else {
				mpz_set_ui(s, step);
				mpz_add(f, f, s);
				over = true;
			}
		} else {
			mpz_add_ui(s, s, k - 2);
			mpz_add(f, f, s);
		}
		visitor_func(&f);
	}
	mpz_clears(f, s, NULL);
}
