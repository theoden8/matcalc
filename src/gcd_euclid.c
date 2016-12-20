#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	mpz_t a, b;
	mpz_inits(a, b, NULL);
	mpz_set_str(a, argv[1], 10);
	mpz_set_str(b, argv[2], 10);
	if(mpz_cmp_si(a, 0) < 0 || mpz_cmp_si(b, 0) < 0) {
		fputs("error: please, pick non-negative integers", stderr);
		return EXIT_FAILURE;
	}
	while(mpz_cmp_si(a, 0) != 0 && mpz_cmp_si(b, 0) != 0) {
		if(mpz_cmp(a, b) > 0)
			mpz_fdiv_r(a, a, b);
		else if(mpz_cmp(a, b) < 0)
			mpz_fdiv_r(b, b, a);
		else break;
	}
	gmp_printf("%Zd\n", (mpz_cmp_si(a, 0) == 0) ? b : a);
	mpz_clears(a, b, NULL);
}
