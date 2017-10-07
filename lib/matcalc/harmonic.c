#include "harmonic.h"

// nth harmonic number is given by:
//  H[n] = 1 + 1/2 + 1/3 + ... = sum(1/i | i <- [1..n])

void calc_harmonic(int n, mpfr_visitor visitor_func) {
  mpfr_t h, one, x;
  mpfr_inits2(PRECISION, h, one, x, NULL);
  mpfr_set_si(h, 0, MPFR_RNDU);
  mpfr_set_si(one, 1, MPFR_RNDU);
  for(int i = 1; i < n; ++i) {
    mpfr_div_ui(x, one, i, MPFR_RNDD);
    mpfr_add(h, h, x, MPFR_RNDU);
    visitor_func(&h);
  }
  mpfr_clears(h, one, x, NULL);
}
