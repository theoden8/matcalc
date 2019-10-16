#ifndef NTH_DERANGEMENTS_H_GNHO5X4E
#define NTH_DERANGEMENTS_H_GNHO5X4E

#include <stdlib.h>
#include <gmp.h>

#include "visitor.h"

void calc_nth_derangement(long n, mpz_visitor visitor_func);

#endif
