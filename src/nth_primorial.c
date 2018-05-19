#include <stdlib.h>

#include <matcalc/nth_primorial.h>

main(int argc, char *argv[]) {
  if(argc != 2)
    return EXIT_FAILURE;
  calc_nth_primorial(atoi(argv[1]), mpz_printer);
}
