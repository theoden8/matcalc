#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <matcalc/visitor.h>
#include <matcalc/nth_fibonacci_binet.h>

// we will use the Binet formula to compute nth fibonacci number straight (approx, though)

main(const argc, char *argv[]) {
	init_phi();
	for(int i = 1; i < argc; ++i) {
		calc_nth_fib_binet(atoi(argv[i]), mpfr_printer);
	}
	clear_phi();
}
