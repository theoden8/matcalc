#ifndef PI_GAUSS_LEGENDRE_H_3Y1TH6EW
#define PI_GAUSS_LEGENDRE_H_3Y1TH6EW

#include <mpfr.h>

static void init_components(mpfr_t a, mpfr_t b, mpfr_t t, mpfr_t p, int precision);
static void pi_iterate(mpfr_t a[2], mpfr_t b[2], mpfr_t t[2], mpfr_t p[2], char head, int precision);
static void pi_calculate(mpfr_t pi, mpfr_t a, mpfr_t b, mpfr_t t);
void calc_pi_gauss_legendre(mpfr_t pi, int no_iters, int prec);

#endif
