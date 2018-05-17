#include "nth_fibonacci.h"

static mpfr_t sqrt_5;

void init_sqrt5() {
	mpfr_init2(sqrt_5, PRECISION);
	mpfr_sqrt_ui(sqrt_5, 5, MPFR_RNDD);
}

void clear_sqrt5() {
	mpfr_clear(sqrt_5);
}

void calc_nth_fib(const long N, mpfr_visitor visitor_func) {
	mpfr_t f, left, right;
	mpfr_inits2(PRECISION, f, left, right, NULL);

	mpfr_add_ui(left, sqrt_5, 1, MPFR_RNDD);
	mpfr_div_ui(left, left, 2, MPFR_RNDD);
	mpfr_pow_ui(left, left, N, MPFR_RNDD);

	mpfr_mul_si(right, sqrt_5, -1, MPFR_RNDD);
	mpfr_add_ui(right, right, 1, MPFR_RNDD);
	mpfr_div_ui(right, right, 2, MPFR_RNDD);
	mpfr_pow_ui(right, right, N, MPFR_RNDD);

	mpfr_sub(left, left, right, MPFR_RNDD);
	mpfr_div(f, left, sqrt_5, MPFR_RNDD);

	visitor_func(&f);

	mpfr_clears(f, left, right, NULL);
}
