#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include <matcalc/visitor.h>
#include <matcalc/figurate.h>

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	const long
		K = atol(argv[1]),
		N = atol(argv[2]);
	calc_figurate(K, N, mpz_printer);
}
