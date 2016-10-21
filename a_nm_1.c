#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

// euler numbers of first kind
// / n \
// \ m /
//
// alike stirling numbers, catalan numbers, binomial coefficients and other
// parts of the zoo, euler numbers mean something to combinatorics: they
// represent the number of permutations with exactly m ascents of a set of size n
//
// formula:
// a(n, m) = sum(i = 1, i <= m + 1, ++i) { (-1)^(m - i + 1) * c(n + 1, m - j + 1) * i^N }


static void misc_mpz_manip_fac_ui(mpz_t src, unsigned long val, void (*manip)(mpz_t, mpz_t, mpz_t)) {
	mpz_t fac;
	mpz_init(fac);
	mpz_fac_ui(fac, val);
	manip(src, src, fac);
	mpz_clear(fac);
}


main(const argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;

	size_t
		n = atoi(argv[1]),
		m = atoi(argv[2]);

	if(m > n) {
		printf("0\n");
		return EXIT_SUCCESS;
	}

	mpz_t
		euler_nm, // accumulated value
		cur, // current term
		pow_n; // i^N

	mpz_inits(euler_nm, cur, pow_n, NULL);

	mpz_set_si(pow_n, 1);
	mpz_set_si(euler_nm, 0);
	mpz_set_si(cur, (m & 1) ? 1 : -1);

	misc_mpz_manip_fac_ui(cur, n + 1, mpz_mul);
	misc_mpz_manip_fac_ui(cur, m + 1, mpz_div);
	misc_mpz_manip_fac_ui(cur, (n + 1) - (m + 1), mpz_div);

	for(size_t i = 1; i <= (m + 1); ++i) {
		/* (-1)^.. */
		mpz_mul_si(cur, cur, -1);

		/* i^N */
		mpz_div(cur, cur, pow_n);
		mpz_ui_pow_ui(pow_n, i, n);
		mpz_mul(cur, cur, pow_n);

		/* c(n, k) */
		const size_t moved = (m - i + 1) + 1;
		mpz_mul_ui(cur, cur, moved);
		mpz_fdiv_q_ui(cur, cur, (n + 1) - moved + 1);

		/* add cur to a_n_k */
		mpz_add(euler_nm, euler_nm, cur);
	}
	gmp_printf("%Zd\n", euler_nm);

	mpz_clears(euler_nm, cur, pow_n, NULL);
}
