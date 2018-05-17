#include "visitor.h"

void visitor_nop(const void *p) {}

void mpz_printer(const mpz_t *val) {
#ifndef NPRINT
	gmp_printf("%Zd\n", *val);
#endif
}

void mpfr_printer(const mpfr_t *val) {
#ifndef NPRINT
	mpfr_printf("%.200RNf\n", *val);
#endif
}
