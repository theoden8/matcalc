#ifndef COLLATZ_H_JCU0YSPB
#define COLLATZ_H_JCU0YSPB

#include "visitor.h"

#include <gmp.h>

void calc_collatz_convergence(const mpz_t N, mpz_visitor visitor_func);


#endif /* end of include guard: COLLATZ_H_JCU0YSPB */
