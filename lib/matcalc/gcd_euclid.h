#ifndef GCD_EUCLID_H_YFAO8FD2
#define GCD_EUCLID_H_YFAO8FD2

#include <stdbool.h>

#include "visitor.h"

bool calc_gcd_euclid(const char *left, const char *right, mpz_visitor visitor_func);

#endif
