#include <stdio.h>
#include <stdlib.h>

#include "probability.h"

#include <mpfr.h>

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	const PRECISION = 2000;
	const long b_N = atol(argv[1]);
	const long double b_P = get_double(2, argv);
	if(b_N < 0 || b_P < 0. || b_P > 1.)
		return EXIT_FAILURE;
	mpfr_t c_nk, p_k, p_nk, term;
	mpfr_inits2(PRECISION, c_nk, p_k, p_nk, term, NULL);

	mpfr_set_ui(c_nk, 1, MPFR_RNDD);
	mpfr_set_d(p_k, b_P, MPFR_RNDD);
	mpfr_ui_sub(p_nk, 1, p_k, MPFR_RNDU);

	mpfr_pow_ui(term, p_nk, b_N - 1, MPFR_RNDU);
	/* mpfr_t sum; */
	/* mpfr_init2(sum, PRECISION); */
	/* mpfr_set_si(sum, 0, MPFR_RNDD); */
	for(size_t k = 0; k < b_N; ++k) {
		mpfr_printf("%.200RNf\n", term);
		/* mpfr_add(sum, sum, term, MPFR_RNDU); */
		mpfr_mul(term, term, p_k, MPFR_RNDD);
		mpfr_div(term, term, p_nk, MPFR_RNDU);
		mpfr_mul_ui(term, term, b_N - k - 1, MPFR_RNDD);
		mpfr_div_ui(term, term, k + 1, MPFR_RNDD);
	}
	/* mpfr_printf("\n%.200RNf\n", sum); */

	mpfr_clears(c_nk, p_k, p_nk, NULL);
}
