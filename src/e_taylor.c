#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

#define PRECISION 20000

/*
 * e = 1/0! + 1/1! + 1/2! + 1/3! + 1/4! + ...
 */

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const long N = atol(argv[1]);
	mpfr_t E, term;
	mpfr_inits2(PRECISION, E, term, NULL);
	mpfr_set_si(term, 1, MPFR_RNDD);
	mpfr_set_si(E, 1, MPFR_RNDD);
	for(size_t i = 1; i < N; ++i) {
		mpfr_div_ui(term, term, i, MPFR_RNDU);
		mpfr_add(E, E, term, MPFR_RNDU);
	}
	mpfr_printf("%.20000RNf\n", E);
	mpfr_clears(E, term, NULL);
}
