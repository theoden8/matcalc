#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <mpfr.h>

#define MPFR_INIT(var) mpfr_init2(var, PRECISION)

main(const argc, char *argv[]) {
	const N = (argc == 2) ? atoi(argv[1]) : 100;
	const PRECISION = 500;
	if(N < 0)
		return EXIT_FAILURE;

	mpfr_t phi, phi_n, rev_phi_n, res;
	MPFR_INIT(phi);
	MPFR_INIT(phi_n);
	MPFR_INIT(rev_phi_n);
	MPFR_INIT(res);

	// phi
	mpfr_sqrt_ui(phi, 5, MPFR_RNDD);
	mpfr_add_si(phi, phi, 1, MPFR_RNDD);
	mpfr_div_si(phi, phi, 2, MPFR_RNDD);
	// phi^N
	mpfr_pow_ui(phi_n, phi, N, MPFR_RNDD);
	// 1/phi^N
	mpfr_set_si(rev_phi_n, 1, MPFR_RNDD);
	mpfr_div(rev_phi_n, rev_phi_n, phi_n, MPFR_RNDD);

	void (*mpfrdo)(mpfr_t, mpfr_t, mpfr_t, mpfr_rnd_t) = (N & 1) ? mpfr_sub : mpfr_add;
	mpfrdo(phi_n, phi_n, rev_phi_n, MPFR_RNDD);
	mpfr_mul_ui(phi, phi, 2, MPFR_RNDD);
	mpfr_add_si(phi, phi, -1, MPFR_RNDD);
	mpfr_div(res, phi_n, phi, MPFR_RNDD);

	mpfr_printf("%.100RNf\n", res);

	mpfr_clears(phi, phi_n, NULL);
}
