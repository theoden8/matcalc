#include "erat_sieve.h"

#include <stdio.h>

typedef struct _int_it {
	uint bit_number; // total index
	uint index; // index in the primes array
	uint bit; // bit inside the array[index]
} int_it;

#define ITER(i) i##_it
#define DECLARE_INT_IT(iter) int_it ITER(iter)
#define BIT_NUMBER(i) ITER(i).bit_number
#define IDX(i) ITER(i).index
#define BIT(i) ITER(i).bit

#define SET_ITER(i) \
	BIT_NUMBER(i) = i / 3 - 1; \
	IDX(i) = BIT_NUMBER(i) / (CHAR_BIT * sizeof(uint)); \
	BIT(i) = 1 << (BIT_NUMBER(i) & (CHAR_BIT * sizeof(uint)) - 1);

#define IS_SET(i) primes[IDX(i)] & BIT(i)
#define UNSET(i) primes[IDX(i)] &= ~BIT(i)

bool prime_printer(uint p) {
	printf("%u\n", p);
	return true;
}

/* static void dump_array(esieve_t *e) { */
/*   int i = 5; */
/*   int j = 0; */
/*   while(i < e->N) { */
/*     if(i >= e->N)break; */
/*     printf("%d", (e->sieve[j / 32] & (1 << j)) ? 1 : 0); */
/*     ++j, i += 2; */
/*     if(i >= e->N)break; */
/*     printf("%d", (e->sieve[j / 32] & (1 << j)) ? 1 : 0); */
/*     ++j, i += 4; */
/*   } */
/*   puts(""); */
/* } */

/* static void dump_sieve(esieve_t *e) { */
/*  uint *primes = e->sieve; */
/* 	printf("primes %u\n", e->N); */
/* 	if(e->N>2)printf("[2]1\n"); */
/* 	if(e->N>3)printf("[3]1\n"); */
/* 	for(uint i = 5; i < e->N; i += 6) { */
/*     DECLARE_INT_IT(i); */
/*     SET_ITER(i); */
/*     if(IS_SET(i)) { */
/*       printf("[%d]1\n", (BIT_NUMBER(i) + 1) * 3 + 2); */
/*     } else { */
/*       printf("[%d]0\n", (BIT_NUMBER(i) + 1) * 3 + 2); */
/*     } */
/*     ++BIT_NUMBER(i); */
/*     BIT(i) <<= 1; */
/*     if(IS_SET(i)) { */
/*       printf("[%d]1\n", (BIT_NUMBER(i) + 1) * 3 + 1); */
/*     } else { */
/*       printf("[%d]0\n", (BIT_NUMBER(i) + 1) * 3 + 1); */
/*     } */
/*   } */
/* } */

uint get_esieve_array_size(uint N) {
	return (((N - 4) / 3) + CHAR_BIT * sizeof(uint) - 1) / (sizeof(uint) * CHAR_BIT);
}

// creates eratosthene sieve struct and fills the 0s and 1s
esieve_t erat_sieve(const uint N) {
	const uint bytes_in_array = get_esieve_array_size(N) * sizeof(uint);
	/* printf("erat sieve: allocate %d bytes\n", bytes_in_array); */
	/* printf("%uMB\n", bytes_in_array / (1024 * 1024)); */
	uint *primes = (uint *)calloc(bytes_in_array, sizeof(uint));
	assert(primes != NULL);

	// The bits in primes follow this pattern:
	//
	// Bit 0 = 5, bit 1 = 7, bit 2 = 11, bit 3 = 13, bit 4 = 17, etc.
	//
	// foreven bits, bit n represents 5 + 6*n
	// forodd  bits, bit n represents 1 + 6*n
	memset(primes, 0xff, bytes_in_array);

	esieve_t e = {
		.sieve = primes,
		.size_of_sieve = bytes_in_array,
		.primes = NULL,
		.mem_primes = 0,
		.no_primes = E_UNDEFINED,
		.N = N,
	};
	/* dump_array(&e); */
	/* dump_sieve(&e); */

	const uint sqrt_N = sqrt(N);
	DECLARE_INT_IT(i);
	DECLARE_INT_IT(j);
	for(uint i = 5; i <= sqrt_N; i += 4) {
		SET_ITER(i);
		if(IS_SET(i)) {
			/* printf("prime: %d [%d %d]\n", i, BIT_NUMBER(i), BIT(i)); */
			const uint increment = 2 * i;
			for(uint j = i * i; j <= N; j += increment) {
				SET_ITER(j);
				UNSET(j);
				/* dump_array(&e); */
				/* printf("unset %d\n", j); */
				j += 1 * increment;
				if(j >= N)break;
				SET_ITER(j);
				UNSET(j);
				/* dump_array(&e); */
				// Skip multiple of 3.
				/* printf("unset %d\n", j); */
				j += 1 * increment;
			}
		} else {
			/* printf("skipped: %d\n", i); */
		}
		i += 2;
		if(i > sqrt_N)break;
		/* SET_ITER(i); */
		BIT(i) <<= 1;
		if(IS_SET(i)) {
			/* printf("prime: %d [%d %d]\n", i, BIT_NUMBER(i), BIT(i)); */
			const uint increment = 2 * i;
			for(uint j = i * i; j <= N; j += increment) {
				SET_ITER(j);
				UNSET(j);
				/* dump_array(&e); */
				/* printf("unset %d\n", j); */
				// Skip multiple of 3.
				j += 2*increment;
				if(j >= N)break;
				SET_ITER(j);
				UNSET(j);
				/* dump_array(&e); */
				/* printf("unset %d\n", j); */
			}
		} else {
			/* printf("skipped: %d\n", i); */
		}
	}
	/* dump_array(&e); */
	return (esieve_t){
		.sieve = primes,
			.size_of_sieve = bytes_in_array,
			.primes = NULL,
			.mem_primes = 0,
			.no_primes = E_UNDEFINED,
			.N = N,
			.capacity = N,
	};
}

// allocates eratosthene sieve
// if N == E_CURRENT
//  return last
// if N == E_UNDEFINED
//  deallocate
// else allocate sieve up to N
esieve_t *get_esieve(uint N) {
	static esieve_t *e = NULL;
	if(N == E_CURRENT) {
		return e;
	} else if(N == E_UNDEFINED) {
		if(e) {
			if(e->primes != NULL) {
				free(e->primes);
			}
			free(e->sieve);
			free(e);
			e = NULL;
		}
	} else if(e && e->capacity < N) {
    e = get_esieve(E_UNDEFINED);
    e = get_esieve(N);
	} else if(e) {
		e->N = N;
	} else if(!e) {
		e = (esieve_t *)malloc(sizeof(esieve_t));
		assert(e != NULL);
		*e = erat_sieve(N);
	}
	return e;
}

// visitor for prime counting
bool vis_inc_no_primes(uint N) {
	esieve_t *e = get_esieve(E_CURRENT);
	if(e->no_primes == E_UNDEFINED) {
    e->no_primes = 0;
  }
	++e->no_primes;
	return true;
}

// fill in e->primes incrementally
bool vis_add_prime(uint N) {
	esieve_t *e=get_esieve(E_CURRENT);
	if(e->primes == NULL) {
		assert(e->no_primes != E_UNDEFINED);
		e->primes = (uint *)malloc(sizeof(uint) * e->no_primes);
		assert(e->primes != NULL);
	}
	e->primes[e->mem_primes++]=N;
	return true;
}

// prime counting function
// fill for random access
uint get_esieve_no_primes() {
	esieve_t *e = get_esieve(E_CURRENT);
	if(e == NULL) {
		abort();
	} else if(e->no_primes == E_UNDEFINED) {
		iter_esieve(e, vis_inc_no_primes);
	}
	return e->no_primes;
}

// get nth prime
uint esieve_nth_prime(const uint N) {
	esieve_t *e = NULL;
	if(N == E_UNDEFINED) {
    // deallocate sieve
		get_esieve(N);
		return E_UNDEFINED;
	}
	e = get_esieve(N);
  // fill the primes array
	get_esieve_no_primes();
	return e->primes[N];
}

/* void isprime(uint n) { */
/*   for(int i = 2; i <= sqrt(n); ++i) { */
/*     assert(n / i * i != n); */
/*   } */
/* } */


// iterate sieve
void iter_esieve(const esieve_t *e, prime_visitor visitor_func) {
	uint *primes = e->sieve;
	DECLARE_INT_IT(i);
	/* dump_sieve(e); */
	if(e->N < 2 || !visitor_func(2))return;
	if(e->N < 3 || !visitor_func(3))return;
	for(uint i = 5; i < e->N; i += 6) {
		SET_ITER(i);
		if(IS_SET(i)) {
			uint p = (BIT_NUMBER(i) + 1) * 3 + 2;
			if(p > e->N)break;
			if(!visitor_func(p))break;
			/* isprime(p); */
		}
		++BIT_NUMBER(i);
		BIT(i) <<= 1;
		if(IS_SET(i)) {
			uint p = (BIT_NUMBER(i) + 1) * 3 + 1;
			if(p > e->N)break;
			if(!visitor_func(p))break;
			/* isprime(p); */
		}
	}
}

#undef ITER
#undef DECLARE_INT_IT
#undef BIT_NUMBER
#undef IDX
#undef BIT
#undef SET_ITER
#undef IS_SET
#undef UNSET
