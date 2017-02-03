#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

// nth_psc means nth row in the pascal triangle
//
// being a genius of math you do understand that this is a sequence of binomial
// coefficients c(n, 0..n)
//
// c(n, k) / c(n, k - 1) = (n - k) / (k + 1) or smth like that, whatever works

#define NPSC_SIZE(x) (((x) >> 1) + 1)

static void calc_nth_row(mpz_t num, int k, int n) {
	if(k == NPSC_SIZE(n))
		return;
	mpz_t me;
	mpz_init(me);
	mpz_set(me, num);

	gmp_printf("%Zd\n", me);

	mpz_mul_ui(num, num, n - k);
	mpz_fdiv_q_ui(num, num, k + 1);

	calc_nth_row(num, k + 1, n);

	if(!(k == NPSC_SIZE(n) - 1)|| n & 1)
		gmp_printf("%Zd\n", me);

	mpz_clear(me);
}

void calc_nth_psc(size_t n) {
	mpz_t num;
	mpz_init(num);
	mpz_set_si(num, 1);
	calc_nth_row(num, 0, n);
	mpz_clear(num);
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	int n = 0;
	sscanf(argv[1], " %d", &n);
	calc_nth_psc(n);
}

#undef NPSC_SIZE
