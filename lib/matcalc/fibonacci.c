#include "fibonacci.h"

// fibonacci are needed everywhere
// but i dont see why you would want to always compute them in the most unreal
// way.
//
// below is the most standard solution for computing the fibonacci sequence
// features:
//  + simplicity
//  + gmp
//  + f(n - 1) + f(n - 2)

void calc_fibs(long n, mpz_visitor visitor_func) {
	if(n == 0)
		return;
	mpz_t tail[3];
	for(int i = 0; i < 3; ++i)
		mpz_init(tail[i]);
	mpz_set_ui(tail[0], 1);
	mpz_set_ui(tail[1], 0);
	mpz_set_ui(tail[2], 1);
	visitor_func(&tail[0]);
	char head = 0, first = 1, second = 2;
	for(long i = 1; i < n; ++i) {
		mpz_add(tail[head], tail[first], tail[second]);
		visitor_func(&tail[head]);
		head = (head + 1) % 3;;
		first = (head + 1) % 3;
		second = (head + 2) % 3;
	}
	for(int i = 0; i < 3; ++i)
		mpz_clear(tail[i]);
}
