#ifndef C_NK_H_XVC4AEL3
#define C_NK_H_XVC4AEL3

#include "visitor.h"

#include <pthread.h>
#include <gmp.h>

typedef enum {
	KFAC, NKFAC, RESFAC,
	FACSIZE
} FAC;

typedef struct _thrfac_t {
	mpz_t *obj;
	unsigned int base;
} thrfac_t;

void calc_c_nk(size_t n, size_t k, mpz_visitor visitor_func);

#endif
