#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <gmp.h>

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

#include "s_nk.h"

void calc_stirling_nk2(st_nk_t *st) {
	const size_t n_k = st->n - st->k + 1;
	for(size_t i = 0; i < st->size; ++i) {
		mpz_t *head = &st->data[i];
		if(i / n_k * n_k == i) {
			mpz_set_si(*head, 1);
		} else if(i < n_k) {
			mpz_set_si(*head, 0);
		} else {
			const mpz_t
				*left = &st->data[i - n_k],
				*right = &st->data[i - 1];
			mpz_mul_ui(*head, *right, (i / n_k));
			mpz_add(*head, *head, *left);
		}
	}
}


main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atol(argv[1]),
		k = atol(argv[2]);

	if(k > n)
		return EXIT_FAILURE;

	st_nk_t st = alloc_st_n_k(n, k);
	calc_stirling_nk2(&st);
	gmp_printf("%Zd\n", st.data[st.size - 1]);
	free_stirling_nk(&st);
}
