#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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

int main(int argc, char *argv[]) {
	seed_rng();
	if(argc != 2)
		return EXIT_FAILURE;
	long n = atol(argv[1]);
	for(long i = 0; i < n; ++i) {
		putchar('0' + rand() % 10);
	}
}
