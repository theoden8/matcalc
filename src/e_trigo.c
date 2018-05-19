#include <stdio.h>
#include <stdlib.h>

#include <mpfr.h>

#define PRECISION 2000

// e^x = sinh(x) + cosh(x)

#include <matcalc/visitor.h>
#include <matcalc/constants.h>

main(int argc, char *argv[]) {
	if(argc != 1 && argc != 2)
		return EXIT_FAILURE;
	const int power = (argc == 2) ? atol(argv[1]) : 1;
	mpfr_t e;
	calc_const_e(&e, power, PRECISION);
	mpfr_printer(&e);
	mpfr_clears(e, NULL);
}
