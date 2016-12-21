#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
#define SZ_UINT sizeof(uint)


#define ITER(i) i##_it
#define DECLARE_INT_IT(iter) int_it ITER(iter)
#define BIT_NUMBER(i) ITER(i).bit_number
#define IDX(i) ITER(i).index
#define BIT(i) ITER(i).bit

#define SET_ITER(i) \
		BIT_NUMBER(i) = i / 3 - 1; \
		IDX(i) = BIT_NUMBER(i) / (8 * sizeof(uint)); \
		BIT(i) = 1 << (BIT_NUMBER(i) & 0x1f);

#define ARRAY primes
#define IS_SET(i) ARRAY[IDX(i)] & BIT(i)
#define UNSET(i) ARRAY[IDX(i)] &= ~BIT(i)

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

main(int argc, char *argv[]) {
	MODE m = set_mode(argc, argv);
	if(m == INVALID) {
		fprintf(stderr, "error: invalid mode");
		return EXIT_FAILURE;
	}

	const uint N = atol(argv[1]);
	const uint size_of_array = (((N + 95) / 96) + 1) * sizeof(uint);
	uint *ARRAY = malloc(size_of_array);
	assert(ARRAY != NULL);

	// The bits in ARRAY follow this pattern:
	//
	// Bit 0 = 5, bit 1 = 7, bit 2 = 11, bit 3 = 13, bit 4 = 17, etc.
	//
	// foreven bits, bit n represents 5 + 6*n
	// forodd  bits, bit n represents 1 + 6*n
	memset(ARRAY , 0xFF, size_of_array);

	const uint sqrt_N = sqrt(N);
	static DECLARE_INT_IT(i);
	static DECLARE_INT_IT(j);
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

	if(m == TIMING)
		goto end;

	// Initial count includes 2, 3.
	MPRINTF("2\n3\n");
	uint count = 2;
	for(uint i = 5; i < N; i += 6) {
		SET_ITER(i);
		if(IS_SET(i)) {
			MPRINTF("%d\n", (BIT_NUMBER(i) + 1) * 3 + 2);
			MCOUNT(++count);
		}
		++BIT_NUMBER(i);
		BIT(i) <<= 1;
		if(IS_SET(i)) {
			MPRINTF("%d\n", (BIT_NUMBER(i) + 1) * 3 + 2);
			MCOUNT(++count);
		}
	}
	if(m == COUNT) {
		printf("\n%d\n", count);
	}

end:
	free(ARRAY);
}
