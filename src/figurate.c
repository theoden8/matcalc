#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include <gmp.h>

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	const long
		K = atol(argv[1]),
		N = atol(argv[2]);
	mpz_t f, s;
	mpz_inits(f, s, NULL);
	mpz_set_si(f, 0);
	const long BREAK = (LONG_MAX - 1) / (K - 2);
	bool over = false;
	for(long i = 0; i < N; ++i) {
		if(!over) {
			long step = 1 + i * (K - 2);
			if((i + 1) < BREAK) {
				mpz_add_ui(f, f, step);
			} else {
				mpz_set_ui(s, step);
				mpz_add(f, f, s);
				over = true;
			}
		} else {
			mpz_add_ui(s, s, K - 2);
			mpz_add(f, f, s);
		}
		gmp_printf("%Zd\n", f);
	}
	mpz_clears(f, s, NULL);
}
