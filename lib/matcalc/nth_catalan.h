#ifndef NTH_CATALAN_H_JTUC9HQK
#define NTH_CATALAN_H_JTUC9HQK

#include <stdlib.h>
#include <gmp.h>

#include "visitor.h"

static void nth_catalan(mpz_t cat, unsigned n);
void calc_nth_catalan(size_t n, mpz_visitor visitor_func);

#endif
