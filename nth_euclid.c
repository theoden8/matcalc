#include <stdio.h>
#include <assert.h>

#include <pthread.h>
#include <gmp.h>


// read natural geographic or smth to learn more about this wild math


#define INTUNDEF -1
typedef unsigned int uint;

void swap(uint *restrict a, uint *restrict b) {
	if(a != b) {
		uint t = *a;
		*a = *b;
		*b = t;
	}
}

pthread_mutex_t mutex;

typedef struct _thrprint_args {
	mpz_t *numbers;
	int size;
} thrprint_args;

void *print_thr_func(void *args) {
	thrprint_args *local = args;
	for(int i = 0; i < local->size; ++i) {
		while(mpz_cmp_si(local->numbers[i], INTUNDEF) == 0)
			;
		gmp_printf("%Zd\n", local->numbers[i]);
	}
	return NULL;
}

void qcksort(uint *arr, int len) {
	if(len < 2)
		return;
	int pivot = 0;
	for(int i = 0; i < len; ++i) {
		if(arr[i] < arr[pivot]) {
			swap(arr + i, arr + pivot);
			pivot = i;
		}
	}
	qcksort(arr, pivot);
	qcksort(arr + pivot + 1, len - pivot);
}

void next_euclid(mpz_t *euclid, mpz_t *tmp) {
	mpz_set(*tmp, *euclid);
	mpz_mul(*euclid, *euclid, *euclid);
	mpz_sub(*euclid, *euclid, *tmp);
	mpz_add_ui(*euclid, *euclid, 1);
}

main(const argc, char *argv[]) {
	int size = argc - 1;

	uint a[size];
	for(int i = 0; i < size; ++i) {
		sscanf(argv[i + 1], " %u", a + i);
	}
	qcksort(a,  size);

	pthread_t thrprint;
	pthread_mutex_t assign_lock;
	thrprint_args thrargs;
	thrargs.size = size;
	for(int i = 0; i < size; ++i) {
		mpz_init(thrargs.numbers[i]);
		mpz_set_si(thrargs.numbers[i], INTUNDEF);
	}
	pthread_mutex_lock(&assign_lock);

	mpz_t euclid, tmp;
	mpz_inits(euclid, tmp, NULL);

	mpz_set_si(euclid, 2);
	int rc;
	// because these numbers are too long, it takes a little bit more time on
	// average to print it as compared to calculating. For this very reason we
	// need another thread to print what is already calculated.
	rc = pthread_create(&thrprint, NULL, print_thr_func, (void *)&thrargs);
	assert(!rc);
	for(int i = 0; i <  size; ++i) {
		assert(a[i] != 0);
		for(int j = (i == 0) ? 1 : a[i - 1]; j < a[i]; ++j) {
			next_euclid(&euclid, &tmp);
		}
		pthread_mutex_lock(&assign_lock);
		mpz_set(thrargs.numbers[i], euclid);
		pthread_mutex_unlock(&assign_lock);
	}
	rc = pthread_join(thrprint, NULL);
	assert(!rc);

	mpz_clears(euclid, tmp, NULL);
	for(int i = 0; i < size; ++i) {
		mpz_clear(thrargs.numbers[i]);
	}
	/* rc = pthread_mutex_destroy(&assign_lock); */
	/* assert(!rc); */
	pthread_exit(NULL);
}
