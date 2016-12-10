#include <assert.h>
#include <stdlib.h>
#include <gmp.h>


// catalan numbers are cowpowers of combinatorics which stand for the total
// possible ways to make up a balanced sequence of range twice as big as the
// index of a catalan number itself
//
// recursively,
//	(1) c(n) = sum(c(i - 1) * c(n - i) | i <- [1..n]) : c(0) = 1
// iteratively,
//  (1) c(n) = c_nk(2n, n) * 1/(n + 1)
//  (2) c(n) = product( 2 * (2 * i - 1) / (i + 1) | i <- [1..n] )


main(const argc, char **argv) {
	if(argc != 2)
		return EXIT_FAILURE;
	const N = atoi(argv[1]);

	if(N < 0)
		return EXIT_FAILURE;
	if(N == 0)
		return EXIT_SUCCESS;

	mpz_t catalan;
	mpz_init(catalan);
	mpz_set_si(catalan, 1);

	gmp_printf("%Zd\n", catalan);
	for(int i = 1; i < N; ++i) {
		mpz_mul_ui(catalan, catalan, 2*(2*i - 1));
		mpz_fdiv_q_ui(catalan, catalan, i + 1);
		gmp_printf("%Zd\n", catalan);
	}
	mpz_clear(catalan);
}
