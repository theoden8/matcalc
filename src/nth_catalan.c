#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

#include <matcalc/visitor.h>
#include <matcalc/nth_catalan.h>

// this one should be raised for charity
// c[n] = 2n! / (n! * (n + 1)!)

main(int argc, char *argv[]) {
	for(int i = 1; i < argc; ++i) {
		calc_nth_catalan(atol(argv[i]), mpz_printer);
	}
}
