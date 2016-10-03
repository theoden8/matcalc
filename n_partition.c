#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef long long llong;

// With euler's pentagonal theorem we can calculate
// p(n) = (-1)^(q + 1) * (p(n - (3q*q - q)/2) + p(n - (3*q*q + q)/2))
//        while (n - (3*q*q + q)/2 >= 0)


// functions to operate on calculated values
llong *alloc_partition_ans(int n) {
	llong *P = malloc(sizeof(llong) * n);
	memset(P, 0x00, sizeof(llong) * n);
	P[0] = P[1] = 1;
	return P;
}

void clear_partition_ans(llong *P) {
	free(P);
}

bool is_set(int x, llong *P) {
	return P[x] != 0ll;
}


// recursive partitioning function
llong partition(int n, llong *P) {
	assert(n >= 0);
	if(is_set(n, P))
		return P[n];

	llong
		sign = 1,
		pent1 = 1, // (3q*q - q)/2
		pent2 = 2, // (3q*q + q)/2
		ret = 0;
	int q = 0;
	while(n - pent2 >= 0) {
		ret += sign * (partition(n - pent1, P) + partition(n - pent2, P));
		++q;
		sign = -sign;
		pent1 += 3*q + 1;
		pent2 += 3*q + 2;
	}
	if(n - pent1 >= 0)
		ret += sign * (partition(n - pent1, P));
	P[n] = ret;
	return ret;
}


main(const argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;

	const
		N = atoi(argv[1]);

	if(N < 0)
		return EXIT_FAILURE;

	llong *P = alloc_partition_ans(N);
	printf("%lld\n", partition(N, P));
	clear_partition_ans(P);
}
