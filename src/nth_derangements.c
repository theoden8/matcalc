#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <matcalc/visitor.h>
#include <matcalc/nth_derangements.h>

// derangement is a permutation of a sequence (1..n) s.t. pmt(i) != i for i in [1..n]
//
// the number of derangements can be computed in recursively as:
//	d(n) = (n - 1) * (d(n - 1) * d(n - 2)) for n >= 3, otherwise {0, 1, 2}
//	d(n) = n*d(n - 1) + (-1)^n
// and iteratively as:
//	d(n) = sum( (-1)^k * (n!/k!) | k <- 0..n )

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const long N = atol(argv[1]);
	if(N < 1)
		return EXIT_FAILURE;
	calc_nth_derangement(N, mpz_printer);
}
