#include "pi_gauss_legendre.h"

// https://en.wikipedia.org/wiki/Gauss%E2%80%93Legendre_algorithm

static void init_components(mpfr_t a, mpfr_t b, mpfr_t t, mpfr_t p, int precision) {
// a:
	mpfr_set_si(a, 1, MPFR_RNDD);
// b:
	mpfr_sqrt_ui(b, 2, MPFR_RNDD);
	mpfr_div(b, a, b, MPFR_RNDN);
// t:
	mpfr_set_si(t, 1, MPFR_RNDD);
	mpfr_div_ui(t, t, 4, GMP_RNDN);
// p:
	mpfr_set_si(p, 1, MPFR_RNDD);
}

static void pi_iterate(mpfr_t a[2], mpfr_t b[2], mpfr_t t[2], mpfr_t p[2], char head, int precision) {
// a_head:
	mpfr_add(a[head], a[!head], b[!head], MPFR_RNDD);
	mpfr_div_ui(a[head], a[head], 2, MPFR_RNDN);
// b_head:
	mpfr_mul(b[head], a[!head], b[!head], MPFR_RNDD);
	mpfr_sqrt(b[head], b[head], MPFR_RNDD);
// t_head:
	mpfr_sub(t[head], a[!head], a[head], MPFR_RNDN);
	mpfr_mul(t[head], t[head], t[head], MPFR_RNDN);
	mpfr_mul(t[head], p[!head], t[head], MPFR_RNDN);
	mpfr_sub(t[head], t[!head], t[head], MPFR_RNDN);
// p_head:
	mpfr_mul_ui(p[head], p[!head], 2, MPFR_RNDN);
}

static void pi_calculate(mpfr_t pi, mpfr_t a, mpfr_t b, mpfr_t t) {
	mpfr_add(pi, a, b, MPFR_RNDN);
	mpfr_mul(pi, pi, pi, MPFR_RNDN);
	mpfr_div(pi, pi, t, MPFR_RNDD);
	mpfr_div_ui(pi, pi, 4, MPFR_RNDD);
}

void calc_pi_gauss_legendre(mpfr_t pi, int no_iters, int prec) {
	mpfr_t a[2], b[2], t[2], p[2];
	mpfr_inits2(prec, pi, a[0], a[1], b[0], b[1], t[0], t[1], p[0], p[1], NULL);
	char head = 0;
	init_components(a[head], b[head], t[head], p[head], prec);
	for(int i = 0; i < no_iters; ++i) {
		head = !head;
		pi_iterate(a, b, t, p, head, prec);
	}
	pi_calculate(pi, a[head], b[head], t[head]);
	mpfr_clears(a[0], a[1], b[0], b[1], t[0], t[1], p[0], p[1], NULL);
}
