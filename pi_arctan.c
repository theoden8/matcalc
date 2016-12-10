#include <stdio.h>
#include <stdlib.h>

#include <mpfr.h>

// the arctangent formula for pi is:
//  pi = 4 * atan(1) = 2 * (sum ( n! / (2*n + 1)!! | n -> infinity) )

main(const argc, char *argv[]) {
	if(argc > 3)
		return EXIT_FAILURE;
	const
		NO_ITERATIONS = (argc >= 2) ? atoi(argv[1]) : (1 << 18),
		PRECISION = (argc == 3) ? atoi(argv[2]) : 20000;
	mpfr_t sum, cur;
	mpfr_inits2(PRECISION, sum, cur, NULL);

	mpfr_set_d(sum, 0.0, MPFR_RNDD);
	mpfr_set_d(cur, 1.0, MPFR_RNDD);
	for(unsigned i = 0; i < NO_ITERATIONS; ++i) {
		if(i > 0)
			mpfr_mul_ui(cur, cur, i, MPFR_RNDD);
		mpfr_div_ui(cur, cur, 2 * i + 1, MPFR_RNDU);
		/* mpfr_printf("%d\t%.20RNf\n", i, cur); */
		mpfr_add(sum, sum, cur, MPFR_RNDU);
	}
	/* mpfr_printf("%.2000RNf\n", sum); */
	mpfr_mul_ui(sum, sum, 2, MPFR_RNDU);
	mpfr_printf("%.2000RNf\n", sum);

	mpfr_clears(sum, cur, NULL);
}
