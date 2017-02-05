#include "pi_arctan.h"

#include "visitor.h"

void calc_pi_arctan(mpfr_t pi, int niters, int nprec) {
	mpfr_t sum, cur;
	mpfr_inits2(nprec, sum, cur, NULL);

	mpfr_set_d(sum, 0.0, MPFR_RNDD);
	mpfr_set_d(cur, 1.0, MPFR_RNDD);
	for(unsigned i = 0; i < niters; ++i) {
		if(i > 0)
			mpfr_mul_ui(cur, cur, i, MPFR_RNDD);
		mpfr_div_ui(cur, cur, 2 * i + 1, MPFR_RNDU);
		/* mpfr_printf("%d\t%.20RNf\n", i, cur); */
		mpfr_add(sum, sum, cur, MPFR_RNDU);
	}
	/* mpfr_printf("%.2000RNf\n", sum); */
	mpfr_mul_ui(sum, sum, 2, MPFR_RNDU);
	mpfr_printer(&sum);

	mpfr_clears(sum, cur, NULL);
}

