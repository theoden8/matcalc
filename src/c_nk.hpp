#ifndef C_NK_HPP_YSEANSZH
#define C_NK_HPP_YSEANSZH


#include "mattemp.hpp"


template <uint N, uint K> struct C_NK {
	declare(uint) C_NK<N - 1, K - 1>::n + C_NK<N - 1, K>::n;
};
template <uint N> struct C_NK <N, N> { declare(uint) 1; };
template <uint N> struct C_NK <N, 0> { declare(uint) 1; };
template <> struct C_NK <0, 0> { declare(uint) 1; };


void statictest_cnk() {
	static_assert(C_NK<0, 0>::n == 1, "");
	static_assert(C_NK<9, 2>::n == 36, "");
	static_assert(C_NK<9, 7>::n == C_NK<9, 7>::n, "");
	static_assert(C_NK<20, 12>::n == 125970, "");
}

#endif
