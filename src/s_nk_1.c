#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// stirling numbers of first kind
// [ n ]
// [ k ]
//
// s1(n, k) is the number of permutations of sets of size n with k cycles
//
// (1) recursive formula:
//  s1(n, k) = {
//	s1(n - 1, k - 1) + (n - 1) * s1(n - 1, k)
//	0 | k == 0
//	0 | k > n
//	1 | n == 0, n == 0
//  }
//
// (2) iterative formula:
//  using tail recursion, we transform the "path" of calculating the s1(n, k)
//  into a loop (zik-zak loop) like this:
//  1 - - - - - - - - - - -
//  1 1 - - - - - - - - - -
//  1 * 1 - - - - - - - - -
//  1 * * 1 - - - - - - - -
//  1 * * * 1 - - - - - - -
//  1 - * * * 1 - - - - - -
//  1 - - * * - 1 - - - - -
//  1 - - - x - - 1 - - - -
//  1 - - - - - - - 1 - - -
//  Therefore, to compute x, we only need to store and compute
//  the elements of the table denoted by '*'.

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
