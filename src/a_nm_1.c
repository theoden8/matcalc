#include <stdio.h>
#include <stdlib.h>

#include <matcalc/visitor.h>
#include <matcalc/a_nm_1.h>

main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atol(argv[1]),
		m = atol(argv[2]);
	calc_anm1(n, m, mpz_printer);
}
