#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

#include <matcalc/visitor.h>

void calc_derangements(const long N, mpz_visitor visitor_func) {
	mpz_t d[3];
	mpz_inits(d[0], d[1], d[2], NULL);
	mpz_set_si(d[0], 0);
	mpz_set_si(d[1], 1);
	mpz_set_si(d[2], 2);
	for(long i = 0; i < ((N <= 3) ? N : 3); ++i) {
		visitor_func(&d[i]);
	}
	char head = 0;
	for(long i = 3; i < N; ++i) {
		char
			l = (head + 2) % 3,
			r = (head + 1) % 3;
		mpz_add(d[head], d[l], d[r]);
		mpz_mul_ui(d[head], d[head], i);
		visitor_func(&d[head]);
		++head;
		if(head == 3)
			head = 0;
	}
	mpz_clears(d[0], d[1], d[2], NULL);
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const long N = atol(argv[1]);
	if(N < 0)
		return EXIT_FAILURE;
	if(N == 0)
		return EXIT_SUCCESS;
	calc_derangements(N, mpz_printer);
}
