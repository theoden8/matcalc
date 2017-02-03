#include <assert.h>

#include "s_nk_1.h"

static void calc_stirling_nk1(st_nk_t *st) {
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
