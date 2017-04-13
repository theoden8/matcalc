#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gmp.h>

#include <matcalc/visitor.h>
#include <matcalc/gcd_euclid.h>

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	if(!calc_gcd_euclid(
		argv[1], argv[2],
		mpz_printer)
	)
	{
		return EXIT_FAILURE;
	}
}
