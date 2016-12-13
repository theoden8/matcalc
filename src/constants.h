#ifndef CONSTANTS_H_QBYSKW72
#define CONSTANTS_H_QBYSKW72

#include <mpfr.h>

void mpfr_const_e(mpfr_t *e, const double power, const int precision) {
	mpfr_t x, esinh, ecosh;
	mpfr_inits2(precision, x, esinh, ecosh, NULL);
	mpfr_set_d(x, power, MPFR_RNDD);
	mpfr_sinh(esinh, x, MPFR_RNDD);
	mpfr_cosh(ecosh, x, MPFR_RNDD);
	mpfr_add(*e, esinh, ecosh, MPFR_RNDD);
	mpfr_clears(x, esinh, ecosh, NULL);
}


#endif
