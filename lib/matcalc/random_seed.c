#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "random_seed.h"

void seed_rng(void) {
	int fp = open("/dev/random", O_RDONLY);
	if(fp == -1)
		abort();
	unsigned
		seed,
		pos = 0;
	while (pos < sizeof(seed)) {
		int amt = read(fp, (char *) &seed + pos, sizeof(seed) - pos);
		if(amt <= 0)
			abort();
		pos += amt;
	}
	srand(seed);
	close(fp);
}
