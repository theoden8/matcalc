#include <stdlib.h>
#include <assert.h>
#include <gmp.h>


// fibonacci are needed everywhere
// but i dont see why you would want to always compute them in the most unreal
// way.
//
// below is the most standard solution for computing the fibonacci sequence
// features:
//  + simplicity
//  + gmp
//  + f(n - 1) + f(n - 2)


main(const argc, char **argv) {
	if(argc != 2)
		return EXIT_FAILURE;
	const N = atoi(argv[1]);

	if(N < 0)
		return EXIT_FAILURE;
	if(N == 0)
		return EXIT_SUCCESS;

	mpz_t tail[3];
	for(int i = 0; i < 3; ++i)
		mpz_init(tail[i]);
	mpz_set_ui(tail[0], 1);
	mpz_set_ui(tail[1], 0);
	mpz_set_ui(tail[2], 0);
	gmp_printf("%Zd\n", tail[0]);
	for(int i = 1; i < N; ++i) {
		mpz_set(tail[2], tail[0]);
		mpz_add(tail[0], tail[1], tail[2]);
		mpz_set(tail[1], tail[2]);
		gmp_printf("%Zd\n", tail[0]);
	}
	for(int i = 0; i < 3; ++i)
		mpz_clear(tail[i]);
}
