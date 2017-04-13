#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <matcalc/a_nm_2.h>
#include <matcalc/visitor.h>

main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atol(argv[1]),
		k = atoi(argv[2]);

	if(k > n)
		return EXIT_FAILURE;
	calc_anm2(n, k, mpz_printer);
}
