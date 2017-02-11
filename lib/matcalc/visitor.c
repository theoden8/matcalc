#include "visitor.h"

void visitor_nop(void *p) {}

void mpz_printer(mpz_t *val) {
#ifndef NPRINT
	gmp_printf("%Zd\n", *val);
#endif
}

void mpfr_printer(mpfr_t *val) {
#ifndef NPRINT
	mpfr_printf("%.200RNf\n", *val);
#endif
}
