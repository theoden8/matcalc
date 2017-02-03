#include <stdlib.h>
#include <stdio.h>

#include <matcalc/random_seed.h>

int main(int argc, char *argv[]) {
	seed_rng();
	if(argc != 2)
		return EXIT_FAILURE;
	long n = atol(argv[1]);
	for(long i = 0; i < n; ++i) {
		putchar('0' + rand() % 10);
	}
}
