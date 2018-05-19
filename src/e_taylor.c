#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

#include <matcalc/e_taylor.h>

/*
 * e = 1/0! + 1/1! + 1/2! + 1/3! + 1/4! + ...
 */

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const long N = atol(argv[1]);
	calc_e_taylor(N, 20000, mpfr_printer);
}
