#ifndef S_NK_HPP_TSOH7XID
#define S_NK_HPP_TSOH7XID


#include "mattemp.hpp"

template <uint N, uint K> struct Stirling1 {
	declare(uint) Stirling1<N - 1, K - 1>::n + (N - 1)*Stirling1<N - 1, K>::n;
};
template <uint N> struct Stirling1 <N, 0> { declare(uint) 0; };
template <uint K> struct Stirling1 <0, K> { declare(uint) 0; };
template <> struct Stirling1 <0, 0> { declare(uint) 1; };

void statictest_snk1() {
	static_assert(Stirling1<0, 0>::n == 1, "");
	static_assert(Stirling1<3, 0>::n == 0, "");
	static_assert(Stirling1<0, 5>::n == 0, "");
	static_assert(Stirling1<6, 4>::n == 85, "");
	static_assert(Stirling1<12, 3>::n == 150917976, "");
}


template <uint N, uint K> struct Stirling2 {
	declare(uint) (K > N) ? 0 : K * Stirling2<N - 1, K>::n + Stirling2<N - 1, K - 1>::n;
};
template <uint N> struct Stirling2 <N, 0> { declare(uint) 0; };
template <uint K> struct Stirling2 <0, K> { declare(uint) 0; };
template <uint N> struct Stirling2 <N, N> { declare(uint) 1; };
template <> struct Stirling2 <0, 0> { declare(uint) 1; };

void statictest_snk2() {
	static_assert(Stirling2<0, 0>::n == 1, "");
	static_assert(Stirling2<5, 0>::n == 0, "");
	static_assert(Stirling2<0, 6>::n == 0, "");
	static_assert(Stirling2<5, 6>::n == 0, "");
	static_assert(Stirling2<19, 6>::n == 693081601779, "");
}

#endif
