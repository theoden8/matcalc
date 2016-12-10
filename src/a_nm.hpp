#ifndef A_NM_HPP_FB1QCWGP
#define A_NM_HPP_FB1QCWGP


#include "mattemp.hpp"

template <uint N, uint M> struct A_NM_1 {
	declare(uint) (N <= M) ? 0 : (M + 1) * A_NM_1<N - 1, M>::n + (N - M) * A_NM_1<N - 1, M - 1>::n;
};
template <uint N> struct A_NM_1 <N, N> { declare(uint) 0; };
template <uint N> struct A_NM_1 <N, 0> { declare(uint) 1; };
template <> struct A_NM_1 <0, 0> { declare(uint) 1; };

void statictest_anm1() {
	static_assert(A_NM_1<0, 0>::n == 1, "");
	static_assert(A_NM_1<1, 0>::n == 1, "");
	static_assert(A_NM_1<2, 0>::n == 1, "");
	static_assert(A_NM_1<1, 1>::n == 0, "");
	static_assert(A_NM_1<16, 16>::n == 0, "");
	static_assert(A_NM_1<16, 15>::n == 1, "");
	static_assert(A_NM_1<15, 7>::n == 447538817472, "");
}


template <uint N, uint M> struct A_NM_2 {
	declare(uint) (N <= M) ? 0 : (2 * N - M - 1) * A_NM_2<N - 1, M - 1>::n + (M + 1) * A_NM_2<N - 1, M>::n;
};
template <uint N> struct A_NM_2 <N, N> { declare(uint) 0; };
template <uint M> struct A_NM_2 <0, M> { declare(uint) 0; };
template <> struct A_NM_2 <0, 0> { declare(uint) 1; };


void statictest_anm2() {
	static_assert(A_NM_2<0, 0>::n == 1, "");
	static_assert(A_NM_2<1, 0>::n == 1, "");
	static_assert(A_NM_2<1, 1>::n == 0, "");
	static_assert(A_NM_2<8, 8>::n == 0, "");
	static_assert(A_NM_2<9, 6>::n == 11026296, "");
}

#endif
