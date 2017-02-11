#include <cstdlib>
#include <climits>

#include <iostream>

#include <gmpxx.h>

static mpz_class pow2(size_t power) {
	mpz_class result;
	mpz_ui_pow_ui(result.get_mpz_t(), 2, power);
	return result;
}

static mpz_class pow2huge(const mpz_class &power) {
	if(power > LONG_MAX) {
		mpz_class half = power / 2;
		return pow2huge(half) * pow2huge(power - half);
	} else {
		return pow2(power.get_ui());
	}
}

mpz_class ackermann(int m, mpz_class n) {
	if(n == 0) {
		return ackermann(m - 1, 1);
	}
	switch(m) {
		case 0:
			return n + 1;
		case 1:
			return n + 2;
		case 2:
			return 2 * n + 3;
		case 3:
			// the recursive formula will be:
			//	  a[3, 1..] = { 13, 2 * a[3, n - 1] + 3 }
			// by converting it to closed formula we get:
			//	  a[3, n] = -3 + 16 * 2^(n - 1)
			return -3 + 16 * pow2huge(n - 1);
		case 4:
			// a(4, n) = [^n + 3](2) - 3
			// where [^n](16) is tetration
			if(n < 3) {
				size_t n_ui = n.get_ui();
				n = 16;
				while(--n_ui != -1ul)
					n = pow2huge(n);
				return n - 3;
			}
		default:
			return ackermann(m - 1, ackermann(m, n - 1));
	}
}

int main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	int m = atoi(argv[1]), n = atoi(argv[2]);
	if(m < 0 || n < 0)
		return EXIT_FAILURE;
	std::cout << ackermann(m, n) << std::endl;
}
