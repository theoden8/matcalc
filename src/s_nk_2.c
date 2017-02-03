#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// stirling numbers of second kind
// { n }
// { k }
//
// s2(n, k) is the number of ways to split a given set of size n into k
// non-empty subsets.
//
// (1) recursive formula:
// s2(n, k) = {
//  k * s2(n - 1, k) + s2(n - 1, k - 1)
//  0 | n == 0 or! k == 0
//  1 | n == k
// }
//
// (2) iterative formula:
//  using tail recursion, we transform the "path" of calculating the s2(n, k)
//  like:
//
//  1 0 0 0 0 0 0 0 0 0
//  0 1 0 - - - - - - 0
//  0 * 1 0 - - - - - 0
//  0 * * 1 0 - - - - 0
//  0 * * * 1 0 - - - 0
//  0 * * * - 1 0 - - 0
//  0 - * * - - 1 0 - 0
//  0 - - x - - - 1 0 0
//  0 - - - - - - - 1 0
//
//  Therefore, we will use the same method as for s1(n, k)

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
