#ifndef S_NK_H_SFA03QPJ
#define S_NK_H_SFA03QPJ


typedef struct _st_n_k {
	mpz_t *data;
	size_t
		n, k,
		size;
} st_nk_t;



st_nk_t alloc_st_n_k(size_t n, size_t k) {
	st_nk_t st = { NULL, n, k, (n - k + 1)*(k + 1) };
	st.data = malloc(sizeof(mpz_t) * st.size);
	for(size_t i = 0; i < st.size; ++i) {
		mpz_init(st.data[i]);
	}
	return st;
}


void free_stirling_nk(st_nk_t *st) {
	for(size_t i = 0; i < st->size; ++i) {
		mpz_clear(st->data[i]);
	}
	free(st->data);
}


#endif /* end of include guard: S_NK_H_SFA03QPJ */
