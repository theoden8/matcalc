#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gmp.h>

#include <matcalc/visitor.h>
#include <matcalc/gcd_euclid.h>

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
  mpz_t a, b;
  mpz_inits(a, b, NULL);
  mpz_set_str(a, argv[1], 10);
  mpz_set_str(b, argv[2], 10);
	if(!calc_gcd_euclid(a, b, mpz_printer)) {
		return EXIT_FAILURE;
	}
  mpz_clears(a, b, NULL);
}
