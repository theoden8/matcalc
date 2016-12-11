#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "probability.h"

#include <mpfr.h>

#define UNDEFINED -1
const PRECISION = 2000;

main(int argc, char *argv[]) {
	if(argc != 3 && argc != 4)
		return EXIT_FAILURE;
	const long b_N = atol(argv[1]);
	const long double b_P = get_double(2, argv);
	const long b_K = ((argc == 4) ? atol(argv[3]) : UNDEFINED);
	if(b_N < 0 || b_P < 0. || b_P > 1.)
		return EXIT_FAILURE;

	mpfr_t p_k, p_nk, pmf;
	mpfr_inits2(PRECISION, p_k, p_nk, pmf, NULL);

	mpfr_set_d(p_k, b_P, MPFR_RNDD);
	mpfr_ui_sub(p_nk, 1, p_k, MPFR_RNDU);

	mpfr_pow_ui(pmf, p_nk, b_N - 1, MPFR_RNDU);
	mpfr_t cdf;
	if(b_K != UNDEFINED) {
		mpfr_init2(cdf, PRECISION);
		mpfr_set_si(cdf, 0, MPFR_RNDD);
	}
	for(size_t k = 0; k < b_N; ++k) {
		if(b_K != UNDEFINED && k >= b_K) {
			mpfr_add(cdf, cdf, pmf, MPFR_RNDU);
		} else if(b_K == UNDEFINED) {
			mpfr_printf("%.200RNf\n", pmf);
		}
		mpfr_mul(pmf, pmf, p_k, MPFR_RNDD);
		mpfr_div(pmf, pmf, p_nk, MPFR_RNDU);
		mpfr_mul_ui(pmf, pmf, b_N - k - 1, MPFR_RNDD);
		mpfr_div_ui(pmf, pmf, k + 1, MPFR_RNDD);
	}
	if(b_K != UNDEFINED) {
		mpfr_printf("%.200RNf\n", cdf);
		mpfr_clear(cdf);
	}

	mpfr_clears(p_k, p_nk, NULL);
}
