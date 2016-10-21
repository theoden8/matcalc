#include <stdlib.h>
#include <assert.h>
#include <gmp.h>


// nobody uses euclid numbers, even myself, but I will add them anyway just
// because I can


#define PRINT(x) gmp_printf("%Zd\n", x)

main(const argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	const N = atoi(argv[1]);

	if(N < 0)
		return EXIT_FAILURE;
	else if(N == 0)
		return EXIT_SUCCESS;

	mpz_t euclid, tmp;
	mpz_inits(euclid, tmp, NULL);
	mpz_set_si(euclid, 2);
	mpz_set(tmp, euclid);

	PRINT(euclid);
	for(int i = 1; i < N; ++i) {
		mpz_set(tmp, euclid);
		mpz_mul(euclid, euclid, euclid);
		mpz_sub(euclid, euclid, tmp);
		mpz_add_ui(euclid, euclid, 1);
		PRINT(euclid);
	}
	mpz_clears(euclid, tmp, NULL);
}
