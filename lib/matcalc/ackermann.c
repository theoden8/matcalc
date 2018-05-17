#include "ackermann.h"

static void pow2(size_t power, mpz_t res) {
  mpz_ui_pow_ui(res, 2, power);
}

static void pow2_huge(mpz_t power, mpz_t res) {
  if(mpz_cmp_ui(power, LONG_MAX) > 0) {
    mpz_t a, b, tmp;
    mpz_inits(a, b, tmp, NULL);
    mpz_fdiv_q_ui(a, power, 2);
    mpz_sub(b, power, a);

    pow2_huge(a, tmp);
    pow2_huge(b, res);
    mpz_mul(res, tmp, res);

    mpz_clears(a, b, tmp, NULL);
  } else {
    unsigned long long pw;
    mpz_export(&pw, 0, -1, sizeof(pw), 0, 0, power);
    pow2(pw, res);
  }
}

void calc_ackermann(int m, size_t n, mpz_visitor visitor_func) {
	if(n == 0) {
		calc_ackermann(m - 1, 1, visitor_func);
	}
  else {
    mpz_t a;
    mpz_init(a);
    switch(m) {
      case 0:
        mpz_set_d(a, n + 1);
      break;
      case 1:
        mpz_set_d(a, n + 2);
      break;
      case 2:
        mpz_set_d(a, 2 * n + 3);
      break;
      case 3:
        // the recursive formula will be:
        //    a[3, 1..] = { 13, 2 * a[3, n - 1] + 3 }
        // by converting it to closed formula we get:
        //    a[3, n] = -3 + 2^(n + 3)
        pow2(n + 3, a);
        mpz_sub_ui(a, a, 3);
      break;
      case 4:
        // a(4, n) = [^n + 3](2) - 3
        // where [^n](16) is tetration
        if(n < 3) {
          mpz_set_d(a, 16);
          size_t n_ui = n;
          while(--n_ui != (size_t)(-1)) {
            pow2_huge(a, a);
          }
          mpz_sub_ui(a, a, 3);
        }
      break;
      default:
        // ack(m - 1, ack(m, n - 1))
        mpz_set_d(a, -1);
      break;
    }
    visitor_func(&a);
    mpz_clear(a);
  }
}
