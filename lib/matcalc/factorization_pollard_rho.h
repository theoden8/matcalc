#ifndef FACTORIZATION_POLLARD_RHO_H_CBO0D2RK
#define FACTORIZATION_POLLARD_RHO_H_CBO0D2RK

#include "visitor.h"

#include <stdlib.h>

void calc_prime_factors_pollard_rho(const mpz_t z, mpz_visitor visitor_func);

#endif /* end of include guard: FACTORIZATION_POLLARD_RHO_H_CBO0D2RK */
