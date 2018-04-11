#include "collatz.h"

#include <stdbool.h>

void calc_collatz_convergence(const mpz_t N, mpz_visitor visitor_func) {
  mpz_t n;
  mpz_inits(n, NULL);
  mpz_set(n, N);
  visitor_func(&n);
  while(mpz_cmp_si(n, 1) != 0) {
    bool parity = mpz_tstbit(n, 0);
    if(!parity) {
      mpz_tdiv_q_ui(n, n, 2);
    } else {
      mpz_mul_ui(n, n, 3);
      mpz_add_ui(n, n, 1);
    }
    visitor_func(&n);
  }
  mpz_clears(n, NULL);
}
