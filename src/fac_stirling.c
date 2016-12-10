#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

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
// stupid approximations correlate with things they are supposed to become
// down to infinity

#define INTUNDEF -1
#define PRECISION 50
#define CONST_STR_E "2.71828182845904523536028747135266249775724709369995"
#define CONST_PRECISION_E (strlen(CONST_STR_E) - strlen("2."))

typedef unsigned long int ULONG;

typedef struct _sequences_t {
	mpfr_t *arr;
	ULONG size;
} seq_t;

#define for_seq(i, seq) for(ULONG i = 0; i < seq->size; ++i)


bool defined(mpfr_t *number) {
	return mpfr_cmp_si(*number, INTUNDEF) != 0;
}

void wait_def(mpfr_t *number) {
	while(!defined(number))
		;
}

void print(seq_t *seq) {
	for_seq(i, seq) {
		wait_def(seq->arr + i);
		mpfr_printf("%.5RNF\n", seq->arr[i]);
	}
}

void nth_term(seq_t *sargs, ULONG idx) {
	mpfr_t *head = sargs->arr + idx;
	assert(!defined(head));
	mpfr_const_pi(*head, MPFR_RNDD);
	mpfr_mul_ui(*head, *head, 2, MPFR_RNDD);
	mpfr_mul_ui(*head, *head, idx, MPFR_RNDD);
	mpfr_root(*head, *head, 2, MPFR_RNDD);

	mpfr_t ne_pow;
	mpfr_init2(ne_pow, PRECISION);
	mpfr_t CONST_E;
	assert(CONST_PRECISION_E == PRECISION);
	mpfr_init2(CONST_E, CONST_PRECISION_E);
	mpfr_set_str(CONST_E, CONST_STR_E, 10, MPFR_RNDD);

	mpfr_set_d(ne_pow, idx, MPFR_RNDD); // n
	mpfr_div(ne_pow, ne_pow, CONST_E, MPFR_RNDD); // n / e
	mpfr_pow_ui(ne_pow, ne_pow, idx, MPFR_RNDD); // (n / e) ^ n

	mpfr_mul(*head, *head, ne_pow, MPFR_RNDD);

	mpfr_clear(ne_pow);
}

void *calc_seq(void *args) {
	seq_t *sargs = args;
	for_seq(i, sargs) {
		nth_term(sargs, i);
	}
	return NULL;
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	unsigned long long N;
	sscanf(argv[1], "%llu", &N);

	mpfr_t arr[N];
	seq_t sequence = { arr, N };
	for_seq(i, (&sequence)) {
		mpfr_init2(sequence.arr[i], PRECISION);
		mpfr_set_si(sequence.arr[i], INTUNDEF, MPFR_RNDD);
	}

	pthread_t thrcalc;

	int rc;
	rc = pthread_create(&thrcalc, NULL, calc_seq, &sequence);
	assert(!rc);
	print(&sequence);
	pthread_join(thrcalc, NULL);

	for_seq(i, (&sequence)) {
		mpfr_clear(sequence.arr[i]);
	}
	mpfr_free_cache();

	pthread_exit(NULL);
}
