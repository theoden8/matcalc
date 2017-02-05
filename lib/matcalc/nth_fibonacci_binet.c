#include "nth_fibonacci_binet.h"

static mpfr_t phi;

void init_phi() {
	mpfr_init2(phi, PRECISION);

	mpfr_sqrt_ui(phi, 5, MPFR_RNDD);
	mpfr_add_si(phi, phi, 1, MPFR_RNDD);
	mpfr_div_si(phi, phi, 2, MPFR_RNDD);
}

void clear_phi() {
	mpfr_clear(phi);
	mpfr_free_cache();
}

void calc_nth_fib_binet(int n, mpfr_visitor visitor_func) {
	mpfr_t fib;
	mpfr_inits2(PRECISION, fib, NULL);

	mpfr_t phix, phi_n, rev_phi_n;
	mpfr_inits2(PRECISION, phix, phi_n, rev_phi_n, NULL);

	mpfr_set(phix, phi, MPFR_RNDD);

	// phi^N
	mpfr_pow_ui(phi_n, phi, n, MPFR_RNDD);
	// 1/phi^N
	mpfr_set_si(rev_phi_n, 1, MPFR_RNDD);
	mpfr_div(rev_phi_n, rev_phi_n, phi_n, MPFR_RNDD);

	void (*mpfrdo)(mpfr_t, mpfr_t, mpfr_t, mpfr_rnd_t) = (n & 1) ? mpfr_sub : mpfr_add;
	mpfrdo(phi_n, phi_n, rev_phi_n, MPFR_RNDD);
	mpfr_mul_ui(phix, phi, 2, MPFR_RNDD);
	mpfr_add_si(phix, phix, -1, MPFR_RNDD);
	mpfr_div(fib, phi_n, phi, MPFR_RNDD);

	visitor_func(&fib);

	mpfr_clears(phix, phi_n, rev_phi_n, NULL);
}
