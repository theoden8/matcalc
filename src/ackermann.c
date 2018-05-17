#include <stdlib.h>
#include <limits.h>

#include <matcalc/visitor.h>
#include <matcalc/ackermann.h>

main(int argc, char *argv[]) {
	if(argc != 3) {
		return EXIT_FAILURE;
	}
	int m = atoi(argv[1]), n = atoi(argv[2]);
	if(m < 0 || n < 0) {
		return EXIT_FAILURE;
	}
  calc_ackermann(m, n, mpz_printer);
}
