#ifndef S_NK_H_SFA03QPJ
#define S_NK_H_SFA03QPJ

#include <gmp.h>

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

st_nk_t alloc_st_n_k(size_t n, size_t k);
void free_stirling_nk(st_nk_t *st);

#endif
