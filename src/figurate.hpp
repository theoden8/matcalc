#ifndef FIGURATE_HPP_QLQZNUI5
#define FIGURATE_HPP_QLQZNUI5


#include "mattemp.hpp"


template <uint K, uint N> struct Figurate {
	declare N * (2 + (K - 2) * (N - 1)) / 2;
};

void statictest_fig() {
	static_assert(Figurate<3, 1>::n == 1, "");
	static_assert(Figurate<3, 2>::n == 3, "");
	static_assert(Figurate<3, 3>::n == 6, "");
	static_assert(Figurate<4, 1>::n == 1, "");
	static_assert(Figurate<4, 2>::n == 4, "");
	static_assert(Figurate<4, 3>::n == 9, "");
	static_assert(Figurate<5, 1>::n == 1, "");
	static_assert(Figurate<5, 2>::n == 5, "");
	static_assert(Figurate<5, 10>::n == 145, "");
	static_assert(Figurate<12, 30>::n == 4380, "");
}


#endif
