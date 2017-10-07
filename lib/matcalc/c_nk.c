#include <assert.h>

#include "c_nk.h"

static void *factorial(void *args) {
	thrfac_t *wrap = args;
	mpz_fac_ui(*wrap->obj, wrap->base);
	return NULL;
}

static void binomial_u(long n, long k, mpz_t *res) {
	assert(n >= 0 && k >= 0);

	mpz_t k_fac, nk_fac;
	mpz_inits(k_fac, nk_fac, NULL);

	pthread_t
		facs[FACSIZE];

	thrfac_t
		facs_data[FACSIZE];

	facs_data[KFAC].obj = &k_fac;
	facs_data[KFAC].base = k;

	facs_data[NKFAC].obj = &nk_fac;
	facs_data[NKFAC].base = n - k;

	facs_data[RESFAC].obj = res;
	facs_data[RESFAC].base = n;

	int rc;
	for(int i = 0; i < FACSIZE; ++i) {
		rc = pthread_create(facs + i, NULL, factorial, (void *)(facs_data + i));
		assert(!rc);
	}
	for(int i = 0; i < FACSIZE; ++i) {
		rc = pthread_join(facs[i], NULL);
		assert(!rc);
	}

	mpz_fdiv_q(*res, *res, k_fac);
	mpz_fdiv_q(*res, *res, nk_fac);

	mpz_clears(k_fac, nk_fac, NULL);
}

static void binomial_s(long n, long k, mpz_t *res) {
	if(n >= 0) {
		binomial_u(n, k, res);
	} else {
		binomial_u(-n + k - 1, k, res);
		if(k & 1)
			mpz_mul_si(*res,* res, -1);
	}
}

void calc_c_nk(size_t n, size_t k, mpz_visitor visitor_func) {
	mpz_t res;
	mpz_init(res);
	binomial_s(n, k, &res);
	visitor_func(&res);
	mpz_clear(res);
}