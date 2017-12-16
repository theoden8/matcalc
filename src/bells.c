#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <matcalc/visitor.h>
#include <matcalc/bells.h>

int main(int argc, char *argv[]) {
  if(argc != 2)  {
    fputs(stderr, "error: need to specify N in arguments");
    return EXIT_FAILURE;
  }

  long n = atol(argv[1]);
  if(n < 0) {
    fputs(stderr, "error: n must be positive");
    return EXIT_FAILURE;
  }

  calc_bells(n, mpz_printer);
}
