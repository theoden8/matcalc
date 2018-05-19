#include "pi_arctan.h"
#include <stdio.h>

#include "visitor.h"

// the arctangent formula for pi is:
//  pi = 4 * atan(1) = 2 * (sum ( n! / (2*n + 1)!! | n -> infinity) )

void calc_pi_arctan(mpfr_t pi, int niters, int nprec) {
	mpfr_t sum, cur;
	mpfr_inits2(nprec, sum, cur, NULL);

	mpfr_set_d(sum, 0.0, MPFR_RNDD);
	mpfr_set_d(cur, 1.0, MPFR_RNDD);
	for(unsigned i = 0; i < niters; ++i) {
		if(i > 0) {
      mpfr_mul_ui(cur, cur, i, MPFR_RNDD);
    }
		mpfr_div_ui(cur, cur, 2 * i + 1, MPFR_RNDU);
		mpfr_printf("%d\t%.20RNf\n", i, cur);
		mpfr_add(sum, sum, cur, MPFR_RNDU);
	}
	mpfr_printf("%.2000RNf\n", sum);
	mpfr_mul_ui(sum, sum, 2, MPFR_RNDU);
  fflush(stdout);
}

