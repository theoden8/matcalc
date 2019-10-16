#ifndef N_PARTITION_H_N54N2YTP
#define N_PARTITION_H_N54N2YTP

#include <stdlib.h>
#include <gmp.h>
#include <omp.h>

#include "visitor.h"

typedef long long llong;

void calc_npartition(long n, mpz_visitor visitor_func);
void calc_npartition_args(long *n, size_t len, mpz_visitor visitor_func);

#endif
