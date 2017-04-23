#include <assert.h>
#include <stdlib.h>

#include <gmp.h>

#include <matcalc/visitor.h>
#include <matcalc/catalans.h>

main(const argc, char **argv) {
	if(argc != 2)
		return EXIT_FAILURE;
	long N = atol(argv[1]);

	if(N < 0)
		return EXIT_FAILURE;
	if(N == 0)
		return EXIT_SUCCESS;

	calc_catalans(N, mpz_printer);
}
