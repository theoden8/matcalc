#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mpfr.h>

#define PRECISION 1000

// using closed formula for fibs we get
// t = sqrt(5)
// f(n) = (1/t) * ( (0.5*(1 - t))^N - (0.5*(1 + t))^N )

void nth_fib(const long N, mpfr_t sqrt_5, mpfr_t *F) {
	mpfr_t
		left, right;
	mpfr_init2(left, PRECISION);
	mpfr_init2(right, PRECISION);

	mpfr_add_ui(left, sqrt_5, 1, MPFR_RNDD);
	mpfr_div_ui(left, left, 2, MPFR_RNDD);
	mpfr_pow_ui(left, left, N, MPFR_RNDD);

	mpfr_mul_si(right, sqrt_5, -1, MPFR_RNDD);
	mpfr_add_ui(right, right, 1, MPFR_RNDD);
	mpfr_div_ui(right, right, 2, MPFR_RNDD);
	mpfr_pow_ui(right, right, N, MPFR_RNDD);

	mpfr_sub(left, left, right, MPFR_RNDD);
	mpfr_div(*F, left, sqrt_5, MPFR_RNDD);

	mpfr_clears(left, right, NULL);
}

main(const argc, char *argv[]) {
	mpfr_t f, sqrt_5;
	mpfr_init2(f, PRECISION);
	mpfr_init2(sqrt_5, PRECISION);

	mpfr_sqrt_ui(sqrt_5, 5, MPFR_RNDD);
	for(int i = 1; i < argc; ++i) {
		nth_fib(atol(argv[i]), sqrt_5, &f);
		mpfr_printf("%.0RNf\n", atol(argv[i]), &f);
	}
	mpfr_clears(f, sqrt_5, NULL);
}
