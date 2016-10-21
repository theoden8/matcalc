#include <stdio.h>
#include <assert.h>

#include <pthread.h>
#include <gmp.h>


// this code is proudly presented to you by your favourite (or not) text editor
// as it can display whatever the darkest souls of computer science (actually,
// it is singular) have put into this file: gmp, pthread, whatever. Hope it
// works on your machine. Use with care.
//
// This is a pascal triangle program. Each row is calculated in a parallel-for loop
// from a previous row (2 arrays of left-palindrome-half length).


#define N 30
#define SIZE(x) (((x) >> 1) + 1)
#define NTHREADS 4

int min(int a, int b) {
	return (a < b) ? a : b;
}

mpz_t row[2][SIZE(N)];
pthread_mutex_t padlock;

typedef struct _tls_t {
	int
		id,
		row_no,
		begin,
		end;
} tls_t;

void *calc_elem(void *args) {
	tls_t *local = (tls_t *)(args);
	for(int j = local->begin; j < local->end; ++j) {
		mpz_add(row[1][j], row[0][j - 1], row[0][j]);
	}
	return NULL;
}


void calc_row(pthread_t threads[NTHREADS], tls_t thrtls[NTHREADS], int i) {
	/* assert(!pthread_mutex_init(&padlock, NULL)); */

	if((i & 1) == 0)
		mpz_set(row[0][SIZE(i) - 1], row[0][SIZE(i) - 2]);

	int rc;
	const int
		t_step = (SIZE(i) + NTHREADS - 1) / NTHREADS,
		nthr = (SIZE(i) + t_step - 1) / t_step;
	for(int t = 0; t < nthr; ++t) {
		thrtls[t].id = t;
		thrtls[t].row_no = i;
		thrtls[t].begin = t_step * t + 1;
		thrtls[t].end = min(t_step * (t + 1) + 1, SIZE(i));
		rc = pthread_create(threads + t, NULL, calc_elem, (void *)(thrtls + t));
		assert(!rc);
	}
	for(int t = 0; t < nthr; ++t) {
		rc = pthread_join(threads[t], NULL);
		assert(!rc);
	}

	/* assert(!pthread_mutex_destroy(&padlock)); */
}


void
	init(),
	clear(),
	print_row(int),
	mirror_rows(int);

void pascal_triangle() {
	pthread_t threads[NTHREADS];
	tls_t thrtls[NTHREADS];
	init();
	for(int i = 0; i < N; ++i) {
		calc_row(threads, thrtls, i);
		print_row(i);
		mirror_rows(i);
	}
	clear();
}


void init() {
	for(int i = 0; i < SIZE(N); ++i) {
		mpz_init(row[0][i]);
		mpz_init(row[1][i]);
		mpz_set_si(row[0][i], 0);
	}
	mpz_set_si(row[0][0], 1);
	mpz_set_si(row[1][0], 1);
}

void print_row(int rsize) {
	int idx = -1;
	for(int i = 0; i <= rsize; ++i) {
		if(i < SIZE(rsize))
			++idx;
		else if(i > SIZE(rsize) || !(rsize & 1))
			--idx;

		assert(idx >= 0 && idx < SIZE(rsize));
		gmp_printf("%Zd ", row[1][idx]);
	}
	gmp_printf("\n");
}

void mirror_rows(int i) {
	for(int j = 0; j < SIZE(i); ++j) {
		mpz_set(row[0][j], row[1][j]);
	}
}

void clear() {
	for(int i = 0; i < SIZE(N); ++i) {
		mpz_clear(row[0][i]);
		mpz_clear(row[1][i]);
	}
	pthread_exit(NULL);
}


main() {
	pascal_triangle();
}
