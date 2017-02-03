#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <matcalc/n_partition.h>
#include <matcalc/visitor.h>

// calculates the number of partions of a given natural number
//
// let n be the number we want to count partitions for.
//
// let M = (1 + x + x^2 + ...) * (1 + (x^2) + (x^2)^2 + ...) * ... * (1 + (x^n) + (x^n)^2 + ...)
//
// We can notice that coeff(expand(M), x^n) = p(n) = number of partitions of n.
//
// Simplify M:
//  M = 1 / ((1 + x) * (1 + x^2) * ... )
//
// Because we are interested in expanding denominator,
// M' = (1 + x) * (1 + x^2) * ... = product(k = 0, inf, 1 + x^k)
//
// Apply euler's pentagonal theorem:
// M' = product(k=0, inf, 1 + x^k) = sum(q=-inf, inf, (-1)^q * x * ((3*q^2 + q) / 2))
//
// p(n) = (-1)^(q + 1) * (p(n - (3q*q - q)/2) + p(n - (3*q*q + q)/2))
//        while (n - (3*q*q + q)/2 >= 0)
//
// We can calculate this using recursion. But wait! For p(n) we need to
// calculate p(n - 1) and p(n - 2) as the first two summons. This means, that
// we can compute this iteratively without having to calculate anything twice.



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
