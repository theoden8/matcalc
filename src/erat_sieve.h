#ifndef ERAT_SIEVE_H_QM8VL6AI
#define ERAT_SIEVE_H_QM8VL6AI

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>

// Thanks to Codereview community and, especially, to JS1, for helping with the
// implementation, which features a wheel (built-in optimisation) of 2 and 3.
//
// http://codereview.stackexchange.com/questions/112901/eratosthenes-sieve-optimized-in-c
//
// this thing might look a little bit fishy, but with solid knowledge of
// computer science one could come to the conclusion that this is, actually,
// code.
//
// I would enjoy seeing the face of anyone looking at this. The sweat should
// come out in the first seven minutes. Than you will start getting red. Another
// few minutes of suffering will drive you crazy. Welcome to __FILE__

typedef struct _int_it {
	int
		bit_number, // total index
		index, // index in the primes array
		bit; // bit inside the array[index]
} int_it;

typedef uint32_t uint;

#define ITER(i) i##_it
#define DECLARE_INT_IT(iter) int_it ITER(iter)
#define BIT_NUMBER(i) ITER(i).bit_number
#define IDX(i) ITER(i).index
#define BIT(i) ITER(i).bit

#define SET_ITER(i) \
		BIT_NUMBER(i) = i / 3 - 1; \
		IDX(i) = BIT_NUMBER(i) / (8 * sizeof(uint)); \
		BIT(i) = 1 << (BIT_NUMBER(i) & 0x1f);

#define ESIEVE primes
#define IS_SET(i) ESIEVE[IDX(i)] & BIT(i)
#define UNSET(i) ESIEVE[IDX(i)] &= ~BIT(i)


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

void iterate_esieve(uint N, void (func(uint))) {
	uint *ESIEVE = erat_sieve(N);
	DECLARE_INT_IT(i);
	DECLARE_INT_IT(j);
	for(uint i = 5; i < N; i += 6) {
		SET_ITER(i);
		if(IS_SET(i))
			func((BIT_NUMBER(i) + 1) * 3 + 2);
		++BIT_NUMBER(i);
		BIT(i) <<= 1;
		if(IS_SET(i))
			func((BIT_NUMBER(i) + 1) * 3 + 1);
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

#endif
