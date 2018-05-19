#include <stdio.h>
#include <stdlib.h>

/*
 * pmf(m) = [ (e^m * m^(-k)) / k! | k <- [0..]
 */

#include <mpfr.h>

#include <matcalc/constants.h>
#include <matcalc/probability.h>

main(int argc, char *argv[]) {
	if(argc != 3 && argc != 4)
		return EXIT_FAILURE;

	const long p_N = atol(argv[1]);
	// argv2 for lambda
	const long p_K = ((argc == 4) ? atol(argv[3]) : UNDEFINED);

	mpfr_t pmf, p_LD, fac, cdf;
	mpfr_inits2(PRECISION, p_LD, fac, NULL);
	if(p_K != UNDEFINED) {
		mpfr_init2(cdf, PRECISION);
		mpfr_set_si(cdf, 0, MPFR_RNDD);
	}
	mpfr_set_str(p_LD, argv[2], 10, MPFR_RNDD);
	if(mpfr_cmp_si(p_LD, 0) < 0) {
		mpfr_clears(p_LD, NULL);
		return EXIT_FAILURE;
	}
	calc_const_e(&pmf, -1, PRECISION);
	mpfr_pow(pmf, pmf, p_LD, MPFR_RNDD);
	for(size_t i = 0; i < p_N; ++i) {
		mpfr_div(pmf, pmf, p_LD, MPFR_RNDD);
		if(i != 0)
			mpfr_div_ui(pmf, pmf, i, MPFR_RNDD);
		if(p_K != UNDEFINED && i <= p_K) {
			mpfr_add(cdf, cdf, pmf, MPFR_RNDU);
		} else if(p_K != UNDEFINED && i > p_K) {
			break;
		} else {
			mpfr_printf("%.200RNf\n", pmf);
		}
	}
	if(p_K != UNDEFINED) {
		mpfr_printf("%.200RNf\n", cdf);
		mpfr_clear(cdf);
	}
	mpfr_clears(pmf, p_LD, fac, NULL);
}
