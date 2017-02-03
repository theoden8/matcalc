#include <stdlib.h>
#include <stdio.h>

#include <matcalc/visitor.h>
#include <matcalc/derangements.h>

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const long N = atol(argv[1]);
	if(N < 0)
		return EXIT_FAILURE;
	if(N == 0)
		return EXIT_SUCCESS;
	calc_derangements(N, mpz_printer);
}
