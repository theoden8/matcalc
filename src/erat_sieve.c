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
uint count = 0;

bool print_and_count(uint n) {
	MPRINTF("%u\n", n);
	MCOUNT(++count);
	return true;
}

main(int argc, char *argv[]) {
	m = set_mode(argc, argv);
	if(m == INVALID) {
		fprintf(stderr, "error: invalid mode");
		return EXIT_FAILURE;
	}
	const uint N = atol(argv[1]);

	if(m == TIMING) {
		free(erat_sieve(N).sieve);
	} else {
		esieve_t *e = get_esieve(N);
		iter_esieve(e, print_and_count);
		MCOUNT(printf("\n%d\n", count));
    get_esieve(E_UNDEFINED);
	}
}
