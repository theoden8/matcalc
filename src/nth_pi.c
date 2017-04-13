#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

#include <mpfr.h>

// we will use plouffe formula for computing nth digit of pi as:
//	pi + 3 = sum( (n * 2^n * n!^2) / (2*n!) | n <- [1..inf])
//

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const PRECISION = 2000;
	const long N = atol(argv[1]);
	if(N < 1)
		return EXIT_FAILURE;
	mpfr_t sum, term, nfac2, n2fac, pow2;
	mpfr_inits2(PRECISION, sum, term, nfac2, n2fac, pow2, NULL);
	mpfr_set_si(sum, 0, MPFR_RNDD);
	mpfr_set_si(nfac2, 1, MPFR_RNDU);
	mpfr_set_si(n2fac, 1, MPFR_RNDU);
	mpfr_set_si(pow2, 1, MPFR_RNDU);
	const long SQRT_N = sqrt(LONG_MAX - 1);
	const long SQRT_N2 = SQRT_N / 2u;
	for(long i = 1; i < N; ++i) {
		// n!^2
		if(i <= SQRT_N) {
			mpfr_mul_ui(nfac2, nfac2, i * i, MPFR_RNDU);
		} else {
			mpfr_mul_ui(nfac2, nfac2, i, MPFR_RNDU);
			mpfr_mul_ui(nfac2, nfac2, i, MPFR_RNDU);
		}
		// 2^n
		mpfr_mul_ui(pow2, pow2, 2, MPFR_RNDU);
		// (2n)!
		if(i <= SQRT_N2) {
			mpfr_mul_ui(n2fac, n2fac, 2*i*(2*i-1), MPFR_RNDU);
		} else {
			mpfr_mul_ui(n2fac, n2fac, 2 * i - 1, MPFR_RNDU);
			mpfr_mul_ui(n2fac, n2fac, 2 * i, MPFR_RNDU);
		}
		// n*(2^n)*(n!^2) / (2n)!
		mpfr_mul_ui(term, pow2, i, MPFR_RNDU);
		mpfr_mul(term, term, nfac2, MPFR_RNDU);
		mpfr_div(term, term, n2fac, MPFR_RNDU);

		/* mpfr_printf("%.200RNf\n", term); */
		mpfr_add(sum, sum, term, MPFR_RNDU);
	}
	mpfr_sub_ui(sum, sum, 3, MPFR_RNDU);
	mpfr_printf("\n%.200RNf\n", term);
	mpfr_clears(sum, term, nfac2, n2fac, pow2, NULL);
}
