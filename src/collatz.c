#include <stdlib.h>
#include <stdio.h>

#include <matcalc/visitor.h>
#include <matcalc/collatz.h>

main(int argc, char *argv[]) {
  if(argc != 2)
    return EXIT_FAILURE;
  mpz_t N;
  mpz_inits(N, NULL);
  mpz_set_str(N, argv[1], 10);
  calc_collatz_convergence(N, mpz_printer);
  mpz_clears(N, NULL);
}
