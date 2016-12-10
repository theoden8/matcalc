#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _erat_t {
	char *sieve;
	int n;
} erat_t;

erat_t *erat = NULL;

static int ersieve_size(int N) {
	return (N / 16) + ((N % 16) != 0);
}

void erat_sieve(const int N) {
	if(erat != NULL || N <= 0) {
		return;
	}
	erat = malloc(sizeof(erat_t));
	erat->sieve = malloc(ersieve_size(N));
	erat->n = 1;
	const int sqrt_n = sqrt(N);
	erat->sieve[]
	for(int i = 3; i <= sqrt_n; ++i) {

	}
}

void free_erat() {
	free(erat->sieve);
	free(erat);
}
