#include <stdio.h>
#include <stdlib.h>

#include <mpfr.h>

#define PRECISION 2000

// e^x = sinh(x) + cosh(x)

#include "constants.h"

main(int argc, char *argv[]) {
	if(argc != 1 && argc != 2)
		return EXIT_FAILURE;
	const int power = (argc == 2) ? atol(argv[1]) : 1;
	mpfr_t e;
	mpfr_inits2(PRECISION, e, NULL);
	mpfr_const_e(&e, power, PRECISION);
	mpfr_clears(e, NULL);
	mpfr_printf("%.200RNf\n", e);
}