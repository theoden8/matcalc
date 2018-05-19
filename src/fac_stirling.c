#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include <matcalc/constants.h>
#include <matcalc/visitor.h>

#include <pthread.h>
#include <mpfr.h>

// stirling!
// this thing calculates factorial approximation using the stirling formula.
// wait, The Stirling Expression, or whatever it is.
//
// So, here we go.
// n! ~= sqrt(2*pi*n) * (n/e)^n
//
// the reason for me to code this formula is just curiosity in how well do
// stupid approximations match with things they are supposed to approximate
// when we use it on a finitely clever computer

#define INTUNDEF -1
#define PRECISION 50

typedef unsigned long int ULONG;

typedef struct _sequences_t {
	mpfr_t *arr;
	ULONG size;
} seq_t;

#define for_seq(i, seq) for(ULONG i = 0; i < seq->size; ++i)


static bool defined(mpfr_t *number) {
	return mpfr_cmp_si(*number, INTUNDEF) != 0;
}

static void wait_def(mpfr_t *number) {
	while(!defined(number))
		;
}

static mpfr_t const_e;
static void nth_term(seq_t *sargs, ULONG idx) {
	static bool e_init = false;
	if(!e_init) {
		e_init = true;
		calc_const_e(&const_e, 1, PRECISION);
	}
	mpfr_t *head = sargs->arr + idx;
	assert(!defined(head));
	mpfr_const_pi(*head, MPFR_RNDN);
	mpfr_mul_ui(*head, *head, idx << 1, MPFR_RNDN);
	mpfr_sqrt(*head, *head, MPFR_RNDN);

	mpfr_t ne_pow;
	mpfr_inits2(PRECISION, ne_pow, NULL);

	mpfr_set_d(ne_pow, idx, MPFR_RNDN); // n
	mpfr_div(ne_pow, ne_pow, const_e, MPFR_RNDN); // n / e
	mpfr_pow_ui(ne_pow, ne_pow, idx, MPFR_RNDN); // (n / e) ^ n

	mpfr_mul(*head, *head, ne_pow, MPFR_RNDN);

	mpfr_clear(ne_pow);
}

static void *calc_seq(void *args) {
	seq_t *sargs = args;
	for_seq(i, sargs) {
		nth_term(sargs, i);
	}
	return NULL;
}

void fac_stirling(unsigned long long N, mpfr_visitor visitor_func) {
	mpfr_t arr[N];
	seq_t sequence = { arr, N };
	for_seq(i, (&sequence)) {
		mpfr_init2(sequence.arr[i], PRECISION);
		mpfr_set_si(sequence.arr[i], INTUNDEF, MPFR_RNDN);
	}

	pthread_t thrcalc;

	int rc;
	rc = pthread_create(&thrcalc, NULL, calc_seq, &sequence);
	assert(!rc);
	for_seq(i, (&sequence)) {
		wait_def(&sequence.arr[i]);
		visitor_func(&sequence.arr[i]);
	}
	pthread_join(thrcalc, NULL);

	for_seq(i, (&sequence)) {
		mpfr_clear(sequence.arr[i]);
	}

	mpfr_free_cache();
	mpfr_clear(const_e);

	pthread_exit(NULL);
}

#undef for_seq

main(int argc, char *argv[]) {
	if(argc != 2) {
		return EXIT_FAILURE;
	}
	unsigned long long N;
	sscanf(argv[1], "%llu", &N);
	fac_stirling(N, mpfr_printer);
}
