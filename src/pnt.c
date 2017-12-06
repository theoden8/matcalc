#include <stdio.h>
#include <stdlib.h>

#include <mpfr.h>

// prime number theorem:
//  pi(n) = |{p | p in P, p < n}| ~= n / log(n)

#define PRECISION 1000

main(int argc, char *argv[]) {
  if(argc != 2)
    return EXIT_FAILURE;
  mpfr_t n, logn;
  mpfr_inits2(PRECISION, n, logn, NULL);
  mpfr_set_str(n, argv[1], 10, MPFR_RNDU);
  mpfr_log(logn, n, MPFR_RNDU);
  mpfr_div(n, n, logn, MPFR_RNDU);
  mpfr_printf("%.0RNf\n", n);
  mpfr_clears(n, NULL);
}
