#ifndef C_NK_HPP_YSEANSZH
#define C_NK_HPP_YSEANSZH


#include "mattemp.hpp"
#include "fac.hpp"


template <uint N, uint K> struct Binomial {
	declare(uint) Binomial<N - 1, K - 1>::n + Binomial<N - 1, K>::n;
};
template <uint N> struct Binomial <N, N> { declare(uint) 1; };
template <uint N> struct Binomial <N, 0> { declare(uint) 1; };
template <> struct Binomial <0, 0> { declare(uint) 1; };


void statictest_cnk() {
	static_assert(Binomial<0, 0>::n == 1, "");
	static_assert(Binomial<9, 2>::n == 36, "");
	static_assert(Binomial<9, 7>::n == Binomial<9, 7>::n, "");
	static_assert(Binomial<20, 12>::n == 125970, "");
}

#endif
