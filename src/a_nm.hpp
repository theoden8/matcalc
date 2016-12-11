#ifndef A_NM_HPP_FB1QCWGP
#define A_NM_HPP_FB1QCWGP


#include "mattemp.hpp"

template <uint N, uint M> struct A_NM_1 {
	declare (N <= M) ? 0 : (M + 1) * A_NM_1<N - 1, M>::n + (N - M) * A_NM_1<N - 1, M - 1>::n;
};
template <uint N> struct A_NM_1 <N, N> { declare 0; };
template <uint N> struct A_NM_1 <N, 0> { declare 1; };
template <> struct A_NM_1 <0, 0> { declare 1; };

template <uint N, uint M> constexpr uint a_nm_1() {
	return A_NM_1<N, M>::n;
}

void statictest_anm1() {
	static_assert(a_nm_1<0, 0>() == 1, "");
	static_assert(a_nm_1<1, 0>() == 1, "");
	static_assert(a_nm_1<2, 0>() == 1, "");
	static_assert(a_nm_1<1, 1>() == 0, "");
	static_assert(a_nm_1<16, 16>() == 0, "");
	static_assert(a_nm_1<16, 15>() == 1, "");
	static_assert(a_nm_1<15, 7>() == 447538817472, "");
}


template <uint N, uint M> struct A_NM_2 {
	declare (N <= M) ? 0 : (2 * N - M - 1) * A_NM_2<N - 1, M - 1>::n + (M + 1) * A_NM_2<N - 1, M>::n;
};
template <uint N> struct A_NM_2 <N, N> { declare 0; };
template <uint M> struct A_NM_2 <0, M> { declare 0; };
template <> struct A_NM_2 <0, 0> { declare 1; };

template <uint N, uint M> constexpr uint a_nm_2() {
	return A_NM_2<N, M>::n;
}


void statictest_anm2() {
	static_assert(a_nm_2<0, 0>() == 1, "");
	static_assert(a_nm_2<1, 0>() == 1, "");
	static_assert(a_nm_2<1, 1>() == 0, "");
	static_assert(a_nm_2<8, 8>() == 0, "");
	static_assert(a_nm_2<9, 6>() == 11026296, "");
}

#endif
