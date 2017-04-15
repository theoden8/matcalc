#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include <matcalc/visitor.h>
#include <matcalc/pi_gauss_legendre.h>

main(const argc, char *argv[]) {
	if(argc > 3)
		return EXIT_FAILURE;
	const
		NO_ITERATIONS = (argc >= 2) ? atoi(argv[1]) : 1000,
		PRECISION = (argc == 3) ? atoi(argv[2]) : 20000;
	mpfr_t pi;
	calc_pi_gauss_legendre(pi, NO_ITERATIONS, PRECISION);
	mpfr_printer(&pi);
	mpfr_clear(pi);
}
