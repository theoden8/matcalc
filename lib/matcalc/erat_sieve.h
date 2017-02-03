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


uint *erat_sieve(const uint N);
void iterate_esieve(uint N, void (visitor_func(uint)));

#endif
