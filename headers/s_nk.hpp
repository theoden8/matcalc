#ifndef S_NK_HPP_TSOH7XID
#define S_NK_HPP_TSOH7XID


#include "mattemp.hpp"

template <muint N, muint K> struct S_NK_1 {
	declare S_NK_1<N - 1, K - 1>::n + (N - 1)*S_NK_1<N - 1, K>::n;
};
template <muint N> struct S_NK_1 <N, 0> { declare 0; };
template <muint K> struct S_NK_1 <0, K> { declare 0; };
template <> struct S_NK_1 <0, 0> { declare 1; };

template <muint N, muint K> constexpr muint s_nk_1 = S_NK_1<N, K>::n;

void statictest_snk1() {
	static_assert(s_nk_1<0, 0> == 1, "");
	static_assert(s_nk_1<3, 0> == 0, "");
	static_assert(s_nk_1<0, 5> == 0, "");
	static_assert(s_nk_1<6, 4> == 85, "");
	static_assert(s_nk_1<12, 3> == 150917976, "");
}


template <muint N, muint K> struct S_NK_2 {
	declare (K > N) ? 0 : K * S_NK_2<N - 1, K>::n + S_NK_2<N - 1, K - 1>::n;
};
template <muint N> struct S_NK_2 <N, 0> { declare 0; };
template <muint K> struct S_NK_2 <0, K> { declare 0; };
template <muint N> struct S_NK_2 <N, N> { declare 1; };
template <> struct S_NK_2 <0, 0> { declare 1; };

template <muint N, muint K> constexpr muint s_nk_2 = S_NK_2<N, K>::n;

void statictest_snk2() {
	static_assert(s_nk_2<0, 0> == 1, "");
	static_assert(s_nk_2<5, 0> == 0, "");
	static_assert(s_nk_2<0, 6> == 0, "");
	static_assert(s_nk_2<5, 6> == 0, "");
	static_assert(s_nk_2<19, 6> == 693081601779, "");
}

#endif
