#include <stdio.h>
#include <stdlib.h>

#include <matcalc/visitor.h>
#include <matcalc/a_nm_1.h>

// euler numbers of first kind
// / n \
// \ m /
//
// alike stirling numbers, catalan numbers, binomial coefficients and other
// parts of the zoo, euler numbers mean something to combinatorics: they
// represent the number of permutations with exactly m ascents of a set of size n
//
// (1) iterative formula:
//  a1(n, m) = sum( (-1)^(m - i + 1) * c(n + 1, m - j + 1) * i^n | i <- [1..m + 1] )
// (2) recursive formula:
//  a1(n, m) = {
//	0 | m > n
//	1 | m == n
//	1 | m=0, n=0
//	(m + 1) * a(n - 1, m) + (n - m) * a(n - 1, m - 1)
//  }

main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atol(argv[1]),
		m = atol(argv[2]);
	calc_anm1(n, m, mpz_printer);
}
