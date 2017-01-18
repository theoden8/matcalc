#ifndef VISITOR_H_U4R8EVIO
#define VISITOR_H_U4R8EVIO

#include <gmp.h>
#include <mpfr.h>

typedef void (mpz_visitor(mpz_t *));
void mpz_printer(mpz_t *val) {
	gmp_printf("%Zd\n", *val);
}

typedef void (mpfr_visitor(mpfr_t *));
void mpfr_printer(mpfr_t *val) {
	mpfr_printf("%.200RNf\n", *val);
}

#endif /* end of include guard: VISITOR_H_U4R8EVIO */
