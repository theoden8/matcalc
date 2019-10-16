#ifndef FAC_HPP_5XRGZLR6
#define FAC_HPP_5XRGZLR6


#include "mattemp.hpp"
#include "pow.hpp"

template <muint N> struct Factorial {
	declare N * Factorial<N - 1>::n;
};
template <> struct Factorial <0> { declare 1; };

template <muint N> superconst muint fac = Factorial<N>::n;

void statictest_fac() {
	static_assert(fac<0> == 1, "");
	static_assert(fac<5> == 120, "");
	static_assert(fac<10> == ProductRange<1, 10>::n, "");
}

#endif
