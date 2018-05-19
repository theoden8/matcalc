#include "nth_primorial.h"

void calc_nth_primorial(size_t n, mpz_visitor visitor_func) {
  mpz_t z;
  mpz_init(z);
  mpz_primorial_ui(z, n);
  visitor_func(&z);
  mpz_clear(z);
}
