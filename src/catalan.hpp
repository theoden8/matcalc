#ifndef CATALAN_HPP_L8YIE2OI
#define CATALAN_HPP_L8YIE2OI


#include "mattemp.hpp"
#include "c_nk.hpp"


template <uint N> struct Catalan {
	declare c_nk<2 * N, N>() / (N + 1);
};

template <uint N> constexpr uint catalan() {
	return Catalan<N>::n;
}


void statictest_catalan() {
	static_assert(catalan<0>() == 1, "");
	static_assert(catalan<1>() == 1, "");
	static_assert(catalan<10>() == 16796, "");
}

#endif
