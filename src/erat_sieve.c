#include <stdlib.h>
#include <stdio.h>

#include <matcalc/erat_sieve.h>

typedef enum {
	COUNT, PRINT, TIMING, INVALID
} MODE;

MODE set_mode(int argc, char *argv[]) {
	if(argc == 2) {
		return TIMING;
	} else if(argc == 3 && strlen(argv[2]) != 1) {
		return INVALID;
	} else if(argc == 3) {
		switch(argv[2][0]) {
			case 'c': return COUNT;
			case 't': return TIMING;
			case 'p': return PRINT;
			default: return INVALID;
		}
	}
	return INVALID;
}

#define MPRINTF if(m == PRINT) printf
#define MCOUNT(what) if(m == COUNT) { what; }

MODE m;
uint count = 2;

void print_and_count(uint n) {
	MPRINTF("%u\n", n);
	MCOUNT(++count);
}

main(int argc, char *argv[]) {
	m = set_mode(argc, argv);
	if(m == INVALID) {
		fprintf(stderr, "error: invalid mode");
		return EXIT_FAILURE;
	}
	const uint N = atol(argv[1]);

	if(m == TIMING) {
		uint *esieve = erat_sieve(N);
		free(esieve);
	} else {
		MPRINTF("2\n3\n");
		iterate_esieve(N, print_and_count);
		MCOUNT(printf("\n%d\n", count));
	}
}
