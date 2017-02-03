#include <omp.h>

#include "s_nk.h"

st_nk_t alloc_st_n_k(size_t n, size_t k) {
	st_nk_t st = { NULL, n, k, (n - k + 1)*(k + 1) };
	st.data = malloc(sizeof(mpz_t) * st.size);
	size_t i;
	#pragma omp for private(i) num_threads(MAXTHREADS)
	for(i = 0; i < st.size; ++i)
		mpz_init(st.data[i]);
	return st;
}


void free_stirling_nk(st_nk_t *st) {
	size_t i;
	#pragma omp for private(i) num_threads(MAXTHREADS)
	for(i = 0; i < st->size; ++i)
		mpz_clear(st->data[i]);
	free(st->data);
}
