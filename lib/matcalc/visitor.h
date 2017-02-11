#ifndef VISITOR_H_U4R8EVIO
#define VISITOR_H_U4R8EVIO

#include <gmp.h>
#include <mpfr.h>

void visitor_nop(void *);

typedef void (mpz_visitor(mpz_t *));
mpz_visitor
	mpz_printer;

typedef void (mpfr_visitor(mpfr_t *));
mpfr_visitor
	mpfr_printer;

#endif /* end of include guard: VISITOR_H_U4R8EVIO */
