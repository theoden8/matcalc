#include <cstdlib>
#include <climits>

#include <iostream>
#include <vector>

#include <gmpxx.h>

const mpz_class UNDEFINED = -1e9;
static const std::size_t MEM3 = 150;
std::vector <mpz_class> threes(MEM3, UNDEFINED);
static const std::size_t MEM4 = 1;
std::vector <mpz_class> fours(MEM4, UNDEFINED);

mpz_class pow2(size_t power) {
	mpz_class result;
	mpz_ui_pow_ui(result.get_mpz_t(), 2, power);
	return result;
}

mpz_class pow2huge(const mpz_class &power) {
	if(power > LONG_MAX) {
		mpz_class half = power / 2;
		return pow2huge(half) * pow2huge(power - half);
	} else {
		return pow2(power.get_ui());
	}
}

mpz_class ackermann(int m, mpz_class n) {
	/* std::cout << m << " " << n << std::endl; */
	if(m == 0)
		return n + 1;
	if(n == 0) {
		return ackermann(m - 1, 1);
	}
	if(m == 1) {
		return n + 2;
	} if(m == 2) {
		return 2 * n + 3;
	}
	if(m == 3 && n < MEM3) {
		size_t idx = n.get_ui();
		if(threes[idx] == UNDEFINED) {
			threes[idx] = 13;
			for(size_t i = 1; i < n; ++i) {
				threes[i] = threes[idx] = threes[idx] * 2 + 3;
			}
		}
		return threes[idx];
	} else if(m == 3) {
		// the recursive formula will be:
		//	  a[3, 1] = 13
		//	  a[3, n] = 2 * a[3, n - 1] + 3
		// by converting it to closed formula we get:
		//	  a[3, n] = -3 + 16 * 2^(n - 1)
		return -3 + 16 * pow2huge(n - 1);
	}
	if(m == 4 && n < 3) {
		// a(4, n) == a(2^16^a(4, n - 1)) - 3
		const size_t n_ui = n.get_ui();
		n = 16;
		for(size_t i = 0; i < n_ui; ++i)
			n = pow2huge(n);
		return n - 3;
	}
	return ackermann(m - 1, ackermann(m, n - 1));
}

int main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	int m = atoi(argv[1]), n = atoi(argv[2]);
	if(m < 0 || n < 0)
		return EXIT_FAILURE;
	std::cout << ackermann(m, n) << std::endl;
}
