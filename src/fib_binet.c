#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <mpfr.h>

// we will use the Binet formula to compute nth fibonacci number straight (approx, though)

#define PRECISION 500

#define MPFR_INIT(var) mpfr_init2(var, PRECISION)

mpfr_t phi;
void nth_fibonacci(mpfr_t fib, int n) {
	mpfr_t phix, phi_n, rev_phi_n;
	MPFR_INIT(phix);
	MPFR_INIT(phi_n);
	MPFR_INIT(rev_phi_n);

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

	mpfr_clears(phix, phi_n, rev_phi_n, NULL);
}

main(const argc, char *argv[]) {
	mpfr_t fib;
	MPFR_INIT(fib);
	MPFR_INIT(phi);
	// phi
	mpfr_sqrt_ui(phi, 5, MPFR_RNDD);
	mpfr_add_si(phi, phi, 1, MPFR_RNDD);
	mpfr_div_si(phi, phi, 2, MPFR_RNDD);

	for(int i = 1; i < argc; ++i) {
		nth_fibonacci(fib, atoi(argv[i]));
		mpfr_printf("%.100RNf\n", fib);
	}


	mpfr_clears(fib, phi, NULL);
	mpfr_free_cache();
}
