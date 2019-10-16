#ifndef GCD_EUCLID_H_YFAO8FD2
#define GCD_EUCLID_H_YFAO8FD2

#include <stdlib.h>
#include <stdbool.h>

#include "visitor.h"

bool calc_gcd_euclid(const mpz_t a, const mpz_t b, mpz_visitor visitor_func);

#endif
