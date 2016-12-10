#ifndef CATALAN_HPP_L8YIE2OI
#define CATALAN_HPP_L8YIE2OI


#include "mattemp.hpp"
#include "c_nk.hpp"


template <uint N> struct Catalan {
	declare(uint) Binomial<2 * N, N>::n / (N + 1);
};


void statictest_catalan() {
	static_assert(Catalan<0>::n == 1, "");
	static_assert(Catalan<1>::n == 1, "");
	static_assert(Catalan<10>::n == 16796, "");
}

#endif
