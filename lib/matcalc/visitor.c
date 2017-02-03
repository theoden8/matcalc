#include "visitor.h"

void mpz_printer(mpz_t *val) {
	gmp_printf("%Zd\n", *val);
}

void mpfr_printer(mpfr_t *val) {
	mpfr_printf("%.200RNf\n", *val);
}
