#ifndef S_NK_H_SFA03QPJ
#define S_NK_H_SFA03QPJ

#include <omp.h>

#ifndef MAXTHREADS
#define MAXTHREADS 8
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// this file provides stirling numbers structure and alloc/free funcs.
// why? because both kinds of numbers store the same data and can be computed
// from the same trace of indexes.
//
// for each computed number of either kind we need to only store and compute the
// parallelogram having the diagonals being (k - 1) recursion and (n == k), and
// straight lines being (n - 1) recursion and (k == 0).


typedef struct _st_n_k {
	mpz_t *data;
	size_t
		n, k,
		size;
} st_nk_t;



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


#endif
