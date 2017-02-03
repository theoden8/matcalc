#include "erat_sieve.h"

uint *erat_sieve(const uint N) {
	#define INTDIFF (8 * sizeof(uint) * 3)
	const uint size_of_array = (((N + (INTDIFF - 1)) / INTDIFF) + 1) * sizeof(uint);
	#undef INTDIFF
	/* printf("%uMB\n", size_of_array / (1024 * 1024)); */
	uint *ESIEVE = malloc(size_of_array);
	assert(ESIEVE != NULL);

	// The bits in ESIEVE follow this pattern:
	//
	// Bit 0 = 5, bit 1 = 7, bit 2 = 11, bit 3 = 13, bit 4 = 17, etc.
	//
	// foreven bits, bit n represents 5 + 6*n
	// forodd  bits, bit n represents 1 + 6*n
	memset(ESIEVE , 0xFF, size_of_array);

	const uint sqrt_N = sqrt(N);
	DECLARE_INT_IT(i);
	DECLARE_INT_IT(j);
	for(uint i = 5; i <= sqrt_N; i += 4) {
		SET_ITER(i);
		if(IS_SET(i)) {
			const uint increment = 2 * i;
			for(uint j = i * i; j < N; j += increment) {
				SET_ITER(j);
				UNSET(j);
				j += 1*increment;
				if(j >= N)
					break;
				SET_ITER(j);
				UNSET(j);
				// Skip multiple of 3.
				j += 1*increment;
			}
		}
		i += 2;
		SET_ITER(i);
		BIT(i) <<= 1;
		if(IS_SET(i)) {
			const uint increment = 2 * i;
			for(uint j = i * i; j < N; j += increment) {
				SET_ITER(j);
				UNSET(j);
				// Skip multiple of 3.
				j += 2*increment;
				if(j >= N)
					break;
				SET_ITER(j);
				UNSET(j);
			}
		}
	}
	return ESIEVE;
}

void iterate_esieve(uint N, void (visitor_func(uint))) {
	uint *ESIEVE = erat_sieve(N);
	DECLARE_INT_IT(i);
	DECLARE_INT_IT(j);
	for(uint i = 5; i < N; i += 6) {
		SET_ITER(i);
		if(IS_SET(i))
			visitor_func((BIT_NUMBER(i) + 1) * 3 + 2);
		++BIT_NUMBER(i);
		BIT(i) <<= 1;
		if(IS_SET(i))
			visitor_func((BIT_NUMBER(i) + 1) * 3 + 1);
	}
	free(ESIEVE);
}

#undef ITER
#undef DECLARE_INT_IT
#undef BIT_NUMBER
#undef IDX
#undef BIT
#undef SET_ITER
#undef ESIEVE
#undef IS_SET
#undef UNSET
