#include <stdio.h>
#include <stdlib.h>

#include "erat_sieve.h"

uint cur = 0;
uint Q;

void prime_counting_iter(uint N) {
	static uint last = 3;
	if(last > Q)
		return;
	for(uint i = last; i < N && i < Q; ++i) {
		printf("%d\n", cur);
	}
	if(N <= Q)
		++cur;
	last = N;
}

uint n_primes_upper(uint N) {
	return ((double)N) * (log(N) + 1);
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	Q = atol(argv[1]);
	if(Q < 2) {
		puts("0");
		return EXIT_SUCCESS;
	} else if(Q == 2) {
		puts("1");
		return EXIT_SUCCESS;
	} else if(Q >= 3) {
		puts("1");
		puts("2");
		cur = 2;
	}
	if(Q == 3)
		return EXIT_SUCCESS;
	iterate_esieve(n_primes_upper(Q), prime_counting_iter);
	printf("%d\n", cur);
}
