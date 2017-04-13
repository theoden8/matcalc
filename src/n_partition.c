#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <matcalc/n_partition.h>
#include <matcalc/visitor.h>

main(const argc, char *argv[]) {
	if(argc == 1)
		return EXIT_SUCCESS;

	long n[argc - 1];
	for(int i = 1; i < argc; ++i) {
		n[i - 1] = atol(argv[i]);
		assert(n[i - 1] >= 0);
	}
	calc_npartition_args(n, argc - 1, mpz_printer);
}
