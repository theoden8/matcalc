#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <matcalc/visitor.h>
#include <matcalc/nth_fibonacci.h>

// using closed formula for fibs we get
// t = sqrt(5)
// f(n) = (1/t) * ( (0.5*(1 - t))^N - (0.5*(1 + t))^N )

main(const argc, char *argv[]) {
	init_sqrt5();
	for(int i = 1; i < argc; ++i) {
		calc_nth_fib(atol(argv[i]), mpfr_printer);
	}
	clear_sqrt5();
}
