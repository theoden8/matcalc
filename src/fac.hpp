#ifndef FAC_HPP_5XRGZLR6
#define FAC_HPP_5XRGZLR6


#include "mattemp.hpp"
#include "pow.hpp"


template <uint N> struct Factorial {
	declare(uint) N * Factorial<N - 1>::n;
};
template <> struct Factorial <0> { declare(uint) 1; };


void statictest_fac() {
	static_assert(Factorial<0>::n == 1, "");
	static_assert(Factorial<5>::n == 120, "");
	static_assert(Factorial<10>::n == ProductRange<1, 10>::n, "");
}

#endif
