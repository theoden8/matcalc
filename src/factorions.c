#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <pthread.h>
#include <gmp.h>

#include <matcalc/threads.h>
#include <matcalc/visitor.h>

// factorion is a sum of factorials of digits

int number_of_threads = 0;

typedef struct _reduce_tls {
	const char *array;
	size_t len;
	mpz_t *res;
} reduce_tls;

int fac(char x) {
	static int facs[10] = {1,0,0,0,0,0,0,0,0};
	if(facs[x] == 0)
		facs[x] = x * fac(x - 1);
	return facs[x];
}

int map_elem(char x) {
	assert(isdigit(x));
	return fac(x - '0');
}

#ifndef MAXTHREADS
#define MAXTHREADS 8
#endif
void *reduce_sum(void *args) {
	reduce_tls *tt = (reduce_tls *)args;

	if(tt->len <= 0) {
		return NULL;
	} else if(tt->len == 1) {
		mpz_add_ui(*tt->res, *tt->res, map_elem(tt->array[0]));
		return NULL;
	}

	size_t mid = tt->len >> 1;

	mpz_t right;
	mpz_init(right);
	mpz_set_si(right, 0);

	bool mt = false;
	pthread_t rthread;
	reduce_tls rt = { tt->array + mid, tt->len - mid, &right };
	tt->len = mid;
	if(number_of_threads < MAXTHREADS / 2) {
		mt = true;
		int rc = pthread_create(&rthread, NULL, reduce_sum, (void *)&rt);
		++number_of_threads;
		assert(rc == 0);
	} else {
		reduce_sum(&rt);
	}
	reduce_sum(tt);
	tt->len = tt->len + rt.len;
	if(mt) {
		int rc = pthread_join(rthread, NULL);
		--number_of_threads;
		assert(rc == 0);
	}

	mpz_add(*tt->res, *tt->res, right);
	mpz_clear(right);
	return NULL;
}

void calc_factorions_args(int argc, char *argv[], mpz_visitor visitor_func) {
	mpz_t res[argc - 1];
	int i;
	#pragma omp parallel for num_threads(MAXTHREADS - (MAXTHREADS / 2))
	for(i = 1; i < argc; ++i) {
		const char *digits = argv[i];
		mpz_init(res[i - 1]);
		mpz_set_si(res[i - 1], 0);
		reduce_tls t = { digits, strlen(digits), &res[i - 1] };
		reduce_sum(&t);
	}
	for(i = 1; i < argc; ++i) {
		visitor_func(&res[i - 1]);
		mpz_clear(res[i - 1]);
	}
}

main(int argc, char *argv[]) {
	calc_factorions_args(argc, argv, mpz_printer);
}
