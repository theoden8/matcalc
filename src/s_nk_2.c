#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <matcalc/s_nk_2.h>
#include <matcalc/visitor.h>

main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atol(argv[1]),
		k = atol(argv[2]);

	if(k > n)
		return EXIT_FAILURE;
	calc_snk2(n, k, mpz_printer);
}
