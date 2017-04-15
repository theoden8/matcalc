#include "pi_newton.h"


// the newtons formula for pi is
//  1 + 1/3(1 + 2/5(1 + 3/7 + (...  )))

void calc_pi_newton(mpfr_t pi, int no_iters, int prec) {
	mpfr_t cur;
	mpfr_inits2(prec, pi, cur, NULL);

	mpfr_set_d(pi, 1.0, MPFR_RNDD);
	for(unsigned int i = 0; i < no_iters; ++i) {
		// TODO finish
		/* mpfr_printf("%d\t%.20RNf\n", i, cur); */
	}
	mpfr_mul_ui(pi, pi, 4, GMP_RNDU);
	mpfr_clear(cur);
}
