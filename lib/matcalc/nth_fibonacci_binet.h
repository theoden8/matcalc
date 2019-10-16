#ifndef NTH_FIBONACCI_BINET_H_ASARNCR8
#define NTH_FIBONACCI_BINET_H_ASARNCR8

#include <stdlib.h>

#include "visitor.h"

#define PRECISION 500

void init_phi();
void calc_nth_fib_binet(int n, mpfr_visitor visitor_func);
void clear_phi();

#endif
