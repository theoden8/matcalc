#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <gmp.h>


// nobody uses euclid numbers, even myself, but I will add them anyway

#include "erat_sieve.h"

mpz_t euclid;
long Q;

void euclid_iter_func(uint N) {
	if(Q <= 0)
		return;
	--Q;
	mpz_mul_ui(euclid, euclid, N);
	mpz_add_ui(euclid, euclid, 1);
	gmp_printf("%Zd\n", euclid);
	mpz_sub_ui(euclid, euclid, 1);
}

main(const argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	Q = atol(argv[1]);

	if(Q < 0)
		return EXIT_FAILURE;
	else if(Q == 0)
		return EXIT_SUCCESS;
	else if(Q == 1) {
		printf("3\n");
		return EXIT_SUCCESS;
	}

	mpz_inits(euclid, NULL);

	printf("3\n7\n");
	Q -= 2;
	mpz_set_si(euclid, 6);
	iterate_esieve((Q + 2) * (Q + 2), euclid_iter_func);
	mpz_clears(euclid, NULL);
}
