#ifndef S_NK_HPP_TSOH7XID
#define S_NK_HPP_TSOH7XID


#include "mattemp.hpp"

template <uint N, uint K> struct S_NK_1 {
	declare(uint) S_NK_1<N - 1, K - 1>::n + (N - 1)*S_NK_1<N - 1, K>::n;
};
template <uint N> struct S_NK_1 <N, 0> { declare(uint) 0; };
template <uint K> struct S_NK_1 <0, K> { declare(uint) 0; };
template <> struct S_NK_1 <0, 0> { declare(uint) 1; };

void statictest_snk1() {
	static_assert(S_NK_1<0, 0>::n == 1, "");
	static_assert(S_NK_1<3, 0>::n == 0, "");
	static_assert(S_NK_1<0, 5>::n == 0, "");
	static_assert(S_NK_1<6, 4>::n == 85, "");
	static_assert(S_NK_1<12, 3>::n == 150917976, "");
}


template <uint N, uint K> struct S_NK_2 {
	declare(uint) (K > N) ? 0 : K * S_NK_2<N - 1, K>::n + S_NK_2<N - 1, K - 1>::n;
};
template <uint N> struct S_NK_2 <N, 0> { declare(uint) 0; };
template <uint K> struct S_NK_2 <0, K> { declare(uint) 0; };
template <uint N> struct S_NK_2 <N, N> { declare(uint) 1; };
template <> struct S_NK_2 <0, 0> { declare(uint) 1; };

void statictest_snk2() {
	static_assert(S_NK_2<0, 0>::n == 1, "");
	static_assert(S_NK_2<5, 0>::n == 0, "");
	static_assert(S_NK_2<0, 6>::n == 0, "");
	static_assert(S_NK_2<5, 6>::n == 0, "");
	static_assert(S_NK_2<19, 6>::n == 693081601779, "");
}

#endif
