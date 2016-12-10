#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

// nth_psc means nth row in the pascal triangle
//
// being a genius of math you do understand that this is a sequence of binomial
// coefficients c(n, 0..n)
//
// c(n, k) / c(n, k - 1) = (n - k) / (k + 1) or smth like that, whatever works

int N;
#define SIZE(x) (((x) >> 1) + 1)

void tab(int x) {
	for(int i = 0; i < x; ++i) {
		gmp_printf("    ");
	}
}

void calc_nth_row(mpz_t num, int k) {
	if(k == SIZE(N))
		return;
	mpz_t me;
	mpz_init(me);
	mpz_set(me, num);

	gmp_printf("%Zd\n", me);

	mpz_mul_ui(num, num, N - k);
	mpz_fdiv_q_ui(num, num, k + 1);

	calc_nth_row(num, k + 1);

	if(!(k == SIZE(N) - 1)|| N & 1)
		gmp_printf("%Zd\n", me);

	mpz_clear(me);
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	sscanf(argv[1], " %d", &N);

	mpz_t num;
	mpz_init(num);
	mpz_set_si(num, 1);
	calc_nth_row(num, 0);
	mpz_clear(num);
}
