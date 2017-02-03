#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <matcalc/c_nk.h>
#include <matcalc/visitor.h>

// binomial coefficients
// ( n )
// ( k )

main(int argc, char *argv[]) {
	if(argc != 3) {
		fputs("invalid number of arguments", stderr);
		return EXIT_FAILURE;
	}

	long n = atol(argv[1]), k = atol(argv[2]);
	if((n < 0 && k >= 0) || n >= k) {
		fputs("invalid arguments", stderr);
		return EXIT_FAILURE;
	}
	calc_c_nk(n, k, mpz_printer);
}
