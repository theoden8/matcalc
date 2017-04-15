#include "pi_leibniz.h"


// the leibniz formula allows to compute pi as
// 1 - 1/3 + 1/5 - 1/7 ... + (-1)^n / (2 * n + 1)
// with the efficiency of about 1.4 decimal points per term (quite weak, but eh)

void calc_pi_leibniz(mpfr_t pi, int no_iters, int prec) {
	mpfr_t cur;
	mpfr_inits2(prec, pi, cur, NULL);

	mpfr_set_d(pi, 0.0, MPFR_RNDD);
	for(unsigned int i = 0; i < no_iters; ++i) {
		mpfr_set_si(cur, (i & 1 ? -1 : 1), MPFR_RNDD);
		mpfr_div_ui(cur, cur, 2 * i + 1, GMP_RNDU);
		mpfr_add(pi, pi, cur, GMP_RNDD);
	}
	mpfr_mul_ui(pi, pi, 4, GMP_RNDU);
}
