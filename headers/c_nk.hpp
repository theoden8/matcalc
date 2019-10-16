#ifndef C_NK_HPP_YSEANSZH
#define C_NK_HPP_YSEANSZH


#include "mattemp.hpp"


template <muint N, muint K> struct C_NK {
	declare C_NK<N - 1, K - 1>::n + C_NK<N - 1, K>::n;
};
template <muint N> struct C_NK <N, N> { declare 1; };
template <muint N> struct C_NK <N, 0> { declare 1; };
template <> struct C_NK <0, 0> { declare 1; };

template <muint N, muint K> superconst muint c_nk = C_NK<N, K>::n;

void statictest_cnk() {
	static_assert(c_nk<0, 0> == 1, "");
	static_assert(c_nk<9, 2> == 36, "");
	static_assert(c_nk<9, 7> == C_NK<9, 7>::n, "");
	static_assert(c_nk<20, 12> == 125970, "");
}

#endif
