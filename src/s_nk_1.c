#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <matcalc/s_nk_1.h>
#include <matcalc/visitor.h>

main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atol(argv[1]),
		k = atol(argv[2]);

	if(k > n)
		return EXIT_FAILURE;
	calc_snk1(n, k, mpz_printer);
}
