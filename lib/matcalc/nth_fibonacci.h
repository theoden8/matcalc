#ifndef NTH_FIBONACCI_H_FKUSC6CA
#define NTH_FIBONACCI_H_FKUSC6CA

#include "visitor.h"

#define PRECISION 1000

void init_sqrt5(), clear_sqrt5();
void calc_nth_fib(const long N, mpfr_visitor visitor_func);

#endif
