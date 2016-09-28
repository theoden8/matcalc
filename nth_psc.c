#include <assert.h>
#include <stdio.h>

#include <gmp.h>

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
	assert(argc == 2);
	sscanf(argv[1], " %d", &N);

	mpz_t num;
	mpz_init(num);
	mpz_set_si(num, 1);
	calc_nth_row(num, 0);
	mpz_clear(num);
}
