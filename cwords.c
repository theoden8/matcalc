#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// consider the alphabet A.
// then if all the symbols of A are 1-byte characters and are a full range from
// some lower thing to some upper, then this program can be used to generate all
// possible words of a given length, iteratively (as opposed to recursively)

#define LOWER '3'
#define UPPER '7'

const inline char lt(char *restrict gr, const n) {
	for(int i = 0; i < n; ++i)
		if(gr[i] < UPPER)
			return 1;
	return 0;
}

main(const argc, char *argv[]) {
	assert(LOWER < UPPER);
	if(argc != 2)
		return EXIT_FAILURE;

	const n = atoi(argv[1]);
	if(n < 0)
		return EXIT_FAILURE;
	char gr[n + 1];
	gr[n] = '\0';
	memset(gr, LOWER, n);
	puts(gr);

	while(lt(gr, n)) {
		for(int i = n - 1; i >= 0; --i)
			if(gr[i] < UPPER) {
				++gr[i];
				break;
			}
			else
				gr[i] = LOWER;
		puts(gr);
	}
}
