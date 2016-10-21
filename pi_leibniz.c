#include <stdio.h>
#include <stdlib.h>

#include <mpfr.h>

// the leibniz formula allows to compute pi as
// 1 - 1/3 + 1/5 - 1/7 ... + (-1)^n / (2 * n + 1)
// with the efficiency of about 1.4 decimal points per term (quite weak, but eh)

main(const argc, char *argv[]) {
	if(argc > 3)
		return EXIT_FAILURE;
	const
		NO_ITERATIONS = (argc >= 2) ? atoi(argv[1]) : (1 << 18),
		PRECISION = (argc == 3) ? atoi(argv[2]) : 20000;
	mpfr_t sum, cur;
	mpfr_init2(sum, PRECISION);
	mpfr_init2(cur, PRECISION);

	mpfr_set_d(sum, 0.0, MPFR_RNDD);
	for(unsigned int i = 0; i < NO_ITERATIONS; ++i) {
		mpfr_set_si(cur, (i & 1 ? -1 : 1), MPFR_RNDD);
		mpfr_div_ui(cur, cur, 2 * i + 1, GMP_RNDU);
		/* mpfr_printf("%d\t%.20RNf\n", i, cur); */
		mpfr_add(sum, sum, cur, GMP_RNDD);
	}
	/* mpfr_printf("%.2000RNf\n", sum); */
	mpfr_mul_ui(sum, sum, 4, GMP_RNDU);
	mpfr_printf("%.2000RNf\n", sum);

	mpfr_clears(sum, cur, NULL);
}
