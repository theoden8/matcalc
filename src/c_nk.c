#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <pthread.h>
#include <gmp.h>


// binomial coefficients
// ( n )
// ( k )
// you should watch discovery or smth if you dont know what it is


typedef enum {
	KFAC, NKFAC, RESFAC,
	FACSIZE
} FAC;

typedef struct _thrfac_t {
	mpz_t *obj;
	unsigned int base;
} thrfac_t;

void *factorial(void *args) {
	thrfac_t *wrap = args;
	mpz_fac_ui(*wrap->obj, wrap->base);
	return NULL;
}

void binomial_u(long n, long k, mpz_t *res) {
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

void binomial_s(long n, long k, mpz_t *res) {
	if(n >= 0) {
		binomial_u(n, k, res);
	} else {
		binomial_u(-n + k - 1, k, res);
		if(k & 1)
			mpz_mul_si(*res,* res, -1);
	}
}

main(int argc, char *argv[]) {
	assert(argc == 3);
	mpz_t res;
	mpz_init(res);

	long n, k;
	sscanf(argv[1], "%ld", &n);
	sscanf(argv[2], "%ld", &k);
	assert((n < 0 && k >= 0) || n >= k);

	binomial_s(n, k, &res);

	gmp_printf("%Zd\n", res);

	mpz_clear(res);
}
