#ifndef ACKERMANN_H_ZCJ1XO94
#define ACKERMANN_H_ZCJ1XO94

#include <stdlib.h>
#include <limits.h>

#include "visitor.h"

#include <gmp.h>

void calc_ackermann(int m, size_t n, mpz_visitor visitor_func);

#endif
