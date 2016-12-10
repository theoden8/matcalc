#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include <mpfr.h>

// https://en.wikipedia.org/wiki/Gauss%E2%80%93Legendre_algorithm

void init_components(mpfr_t *a, mpfr_t *b, mpfr_t *t, mpfr_t *p, int precision) {
// a:
	mpfr_set_si(*a, 1, MPFR_RNDD);
// b:
	mpfr_sqrt_ui(*b, 2, MPFR_RNDD);
	mpfr_div(*b, *a, *b, MPFR_RNDU);
// t:
	mpfr_set_si(*t, 1, MPFR_RNDD);
	mpfr_div_ui(*t, *t, 4, GMP_RNDU);
// p:
	mpfr_set_si(*p, 1, MPFR_RNDD);
}

void pi_iterate(mpfr_t a[2], mpfr_t b[2], mpfr_t t[2], mpfr_t p[2], char head, int precision) {
// a_head:
	mpfr_add(a[head], a[!head], b[!head], MPFR_RNDD);
	mpfr_div_ui(a[head], a[head], 2, MPFR_RNDU);
// b_head:
	mpfr_mul(b[head], a[!head], b[!head], MPFR_RNDD);
	mpfr_sqrt(b[head], b[head], MPFR_RNDD);
// t_head:
	mpfr_sub(t[head], a[!head], a[head], MPFR_RNDU);
	mpfr_mul(t[head], t[head], t[head], MPFR_RNDU);
	mpfr_mul(t[head], p[!head], t[head], MPFR_RNDU);
	mpfr_sub(t[head], t[!head], t[head], MPFR_RNDU);
// p_head:
	mpfr_mul_ui(p[head], p[!head], 2, MPFR_RNDU);
}

void pi_calculate(mpfr_t *pi, mpfr_t *a, mpfr_t *b, mpfr_t *t) {
	mpfr_add(*pi, *a, *b, MPFR_RNDU);
	mpfr_mul(*pi, *pi, *pi, MPFR_RNDU);
	mpfr_div(*pi, *pi, *t, MPFR_RNDD);
	mpfr_div_ui(*pi, *pi, 4, MPFR_RNDD);
}

main(const argc, char *argv[]) {
	if(argc > 3)
		return EXIT_FAILURE;
	const
		NO_ITERATIONS = (argc >= 2) ? atoi(argv[1]) : 1000,
		PRECISION = (argc == 3) ? atoi(argv[2]) : 20000;
	mpfr_t pi, a[2], b[2], t[2], p[2];
	mpfr_inits2(PRECISION, pi, a[0], a[1], b[0], b[1], t[0], t[1], p[0], p[1], NULL);
	char head = 0;
	init_components(&a[head], &b[head], &t[head], &p[head], PRECISION);
	for(int i = 0; i < NO_ITERATIONS; ++i) {
		head = !head;
		pi_iterate(a, b, t, p, head, PRECISION);
	}
	pi_calculate(&pi, &a[head], &b[head], &t[head]);
	mpfr_printf("%.20000RNf\n", pi);
	mpfr_clears(pi, a[0], a[1], b[0], b[1], t[0], t[1], p[0], p[1], NULL);
}
