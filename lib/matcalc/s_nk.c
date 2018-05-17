#include <stdlib.h>

#include "s_nk.h"
#include "threads.h"

st_nk_t alloc_st_n_k(size_t n, size_t k) {
	st_nk_t st = { NULL, n, k, (n - k + 1)*(k + 1) };
	st.data = (mpz_t *)malloc(sizeof(mpz_t) * st.size);
	#pragma omp parallel for
	for(size_t i = 0; i < st.size; ++i) {
		mpz_init(st.data[i]);
	}
	return st;
}


void free_stirling_nk(st_nk_t *st) {
	#pragma omp parallel for
	for(size_t i = 0; i < st->size; ++i) {
		mpz_clear(st->data[i]);
	}
	free(st->data);
}
