#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <matcalc/visitor.h>
#include <matcalc/nth_derangements.h>

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const long N = atol(argv[1]);
	if(N < 1)
		return EXIT_FAILURE;
	calc_nth_derangement(N, mpz_printer);
}
