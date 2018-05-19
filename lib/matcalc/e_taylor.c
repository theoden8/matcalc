#include "e_taylor.h"

void calc_e_taylor(int niters, int prec, mpfr_visitor visitor_func) {
	mpfr_t e, term;
	mpfr_inits2(prec, e, term, NULL);
	mpfr_set_si(term, 1, MPFR_RNDD);
	mpfr_set_si(e, 1, MPFR_RNDD);
	for(size_t i = 1; i < niters; ++i) {
		mpfr_div_ui(term, term, i, MPFR_RNDU);
		mpfr_add(e, e, term, MPFR_RNDU);
	}
	visitor_func(&e);
	mpfr_clears(e, term, NULL);
}
