#ifndef CATALAN_HPP_L8YIE2OI
#define CATALAN_HPP_L8YIE2OI


#include "mattemp.hpp"
#include "c_nk.hpp"


template <muint N> struct Catalan {
	declare C_NK<2 * N, N>::n / (N + 1);
};

template <muint N> superconst muint catalan = Catalan<N>::n;


void statictest_catalan() {
	static_assert(catalan<0> == 1, "");
	static_assert(catalan<1> == 1, "");
	static_assert(catalan<10> == 16796, "");
}

#endif
