#ifndef ERAT_SIEVE_H_QM8VL6AI
#define ERAT_SIEVE_H_QM8VL6AI

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "visitor.h"

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

typedef uint32_t uint;

typedef struct _esieve_t {
	uint *sieve;
	uint size_of_sieve;
	uint *primes;
	uint mem_primes;
	uint no_primes;
	uint N;
	uint capacity;
} esieve_t;

typedef bool prime_visitor(uint);

prime_visitor
  prime_printer;

esieve_t erat_sieve(const uint N);
#define E_CURRENT ((uint)-122)
#define E_UNDEFINED ((uint)(-123))
esieve_t *get_esieve(uint N);
uint get_esieve_no_primes();
uint esieve_nth_prime(const uint N);
void iter_esieve(const esieve_t *e, prime_visitor visitor_func);

#endif
