#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <gmp.h>

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

#include "s_nk.h"
#include "visitor.h"

void calc_stirling_nk1(st_nk_t *st) {
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
			mpz_mul_ui(*head, *right, (i % n_k) + (i / n_k) - 1);
			mpz_add(*head, *head, *left);
		}
	}
}

void calc_snk1(size_t n, size_t k, mpz_visitor visitor_func) {
	st_nk_t st = alloc_st_n_k(n, k);
	calc_stirling_nk1(&st);
	visitor_func(&st.data[st.size - 1]);
	free_stirling_nk(&st);
}

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
