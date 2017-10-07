#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

#include <matcalc/visitor.h>
#include <matcalc/harmonic.h>

main(const argc, char **argv) {
  if(argc != 2) {
    fputs(stderr, "not enough arguments");
    return EXIT_FAILURE;
  }
  int n = atoi(argv[1]);
  if(n < 0) {
    fputs(stderr, "invalid argument");
    return EXIT_FAILURE;
  }

  calc_harmonic(n, mpfr_printer);
}
