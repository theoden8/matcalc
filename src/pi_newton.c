#include <stdio.h>
#include <stdlib.h>

#include <mpfr.h>

// the newtons formula for pi is
//  1 + 1/3(1 + 2/5(1 + 3/7 + (...  )))

main(const argc, char *argv[]) {
	if(argc > 3)
		return EXIT_FAILURE;
	const
		NO_ITERATIONS = (argc >= 2) ? atoi(argv[1]) : (1 << 18),
		PRECISION = (argc == 3) ? atoi(argv[2]) : 20000;
	mpfr_t acc_pi, cur;
	mpfr_inits2(PRECISION, acc_pi, cur, NULL);

	mpfr_set_d(acc_pi, 1.0, MPFR_RNDD);
	for(unsigned int i = 0; i < NO_ITERATIONS; ++i) {
		/* mpfr_printf("%d\t%.20RNf\n", i, cur); */
	}
	/* mpfr_printf("%.2000RNf\n", acc_pi); */
	mpfr_mul_ui(acc_pi, acc_pi, 4, GMP_RNDU);
	mpfr_printf("%.2000RNf\n", acc_pi);

	mpfr_clears(acc_pi, cur, NULL);
}
