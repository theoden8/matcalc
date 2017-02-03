#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <gmp.h>

#include <matcalc/s_nk.h>
#include <matcalc/visitor.h>

// euler numbers of second kind
// // n \\
// \\ k //

static void calc_euler_nk2(st_nk_t *st) {
	const size_t n_k = st->n - st->k + 1;
	mpz_t tmp;
	mpz_init(tmp);
	for(size_t i = 0; i < st->size; ++i) {
		mpz_t *head = &st->data[i];
		const size_t
			n = (i % n_k) + (i / n_k),
			m = i / n_k;
		if(i == 0) {
			mpz_set_si(*head, 1);
		} else if(n == m) {
			mpz_set_si(*head, 0);
		} else if(m < 1) {
			mpz_set_si(*head, 1);
		} else {
			const mpz_t
				*left = &st->data[i - n_k],
				*right = &st->data[i - 1];
			mpz_mul_ui(*head, *left, 2*n - m - 1);
			mpz_mul_ui(tmp, *right, m + 1);
			mpz_add(*head, *head, tmp);
		}
	}
	mpz_clear(tmp);
}

void calc_anm2(size_t n, size_t k, mpz_visitor visitor_func) {
	st_nk_t st = alloc_st_n_k(n, k);
	calc_euler_nk2(&st);
	visitor_func(&st.data[st.size - 1]);
	free_stirling_nk(&st);
}

main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atol(argv[1]),
		k = atoi(argv[2]);

	if(k > n)
		return EXIT_FAILURE;
	calc_anm2(n, k, mpz_printer);
}
