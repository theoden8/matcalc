#include <stdio.h>
#include <stdlib.h>

#include <matcalc/visitor.h>
#include <matcalc/pi_leibniz.h>

main(const argc, char *argv[]) {
	if(argc > 3)
		return EXIT_FAILURE;
	const
		NO_ITERATIONS = (argc >= 2) ? atoi(argv[1]) : (1 << 18),
		PRECISION = (argc == 3) ? atoi(argv[2]) : 20000;
	mpfr_t pi;
	calc_pi_leibniz(pi, NO_ITERATIONS, PRECISION);
	mpfr_printer(&pi);
	mpfr_clear(pi);
}
