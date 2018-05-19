#include "nth_fibonacci.h"

static mpfr_t sqrt_5;

void calc_nth_fib(const long N, mpfr_visitor visitor_func) {
	mpfr_t f, left, right;
	mpfr_inits2(PRECISION, sqrt_5, f, left, right, NULL);
	mpfr_sqrt_ui(sqrt_5, 5, MPFR_RNDN);

  // ((sqrt(5) + 1) / 2)^n
	mpfr_add_ui(left, sqrt_5, 1, MPFR_RNDN);
	mpfr_div_ui(left, left, 2, MPFR_RNDN);
	mpfr_pow_ui(left, left, N, MPFR_RNDN);

  // ((-sqrt(5) + 1) / 2)^n
  mpfr_mul_ui(right, sqrt_5, -1, MPFR_RNDN);
	mpfr_sub_ui(right, right, 1, MPFR_RNDN);
	mpfr_div_ui(right, right, 2, MPFR_RNDN);
	mpfr_pow_ui(right, right, N, MPFR_RNDN);

  // (((s(5) + 1) / 2)^n - ((-s(5) + 1) / 2)^n) / s(5)
	mpfr_sub(left, left, right, MPFR_RNDN);
	mpfr_div(f, left, sqrt_5, MPFR_RNDN);

	visitor_func(&f);

	mpfr_clears(sqrt_5, f, left, right, NULL);
}
