#ifndef FIGURATE_HPP_QLQZNUI5
#define FIGURATE_HPP_QLQZNUI5


#include "mattemp.hpp"


template <uint K, uint N> struct Figurate {
	declare N * (2 + (K - 2) * (N - 1)) / 2;
};

template <uint K, uint N> superconst uint figurate = Figurate<K, N>::n;

void statictest_fig() {
	static_assert(figurate<3, 1> == 1, "");
	static_assert(figurate<3, 2> == 3, "");
	static_assert(figurate<3, 3> == 6, "");
	static_assert(figurate<4, 1> == 1, "");
	static_assert(figurate<4, 2> == 4, "");
	static_assert(figurate<4, 3> == 9, "");
	static_assert(figurate<5, 1> == 1, "");
	static_assert(figurate<5, 2> == 5, "");
	static_assert(figurate<5, 10> == 145, "");
	static_assert(figurate<12, 30> == 4380, "");
}


#endif
