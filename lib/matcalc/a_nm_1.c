#include "a_nm_1.h"

static void misc_mpz_manip_fac_ui(mpz_t src, unsigned long val, void (*manip)(mpz_t, mpz_t, mpz_t)) {
	mpz_t fac;
	mpz_init(fac);
	mpz_fac_ui(fac, val);
	manip(src, src, fac);
	mpz_clear(fac);
}

void calc_anm1(size_t n, size_t m, mpz_visitor visitor_func) {
	if(m > n) {
		mpz_t res;
		mpz_init(res);
		mpz_set_si(res, 0);
		visitor_func(&res);
		mpz_clear(res);
		return;
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
	visitor_func(&euler_nm);

	mpz_clears(euler_nm, cur, pow_n, NULL);
}
