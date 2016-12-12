#ifndef DERANGEMENTS_HPP_Y1XK0GBZ
#define DERANGEMENTS_HPP_Y1XK0GBZ


#include "mattemp.hpp"


template <uint N> struct Derangements {
	declare N * Derangements<N - 1>::n + ((N & 1) ? -1 : 1);
};
template <> struct Derangements <1> { declare 0; };
template <> struct Derangements <2> { declare 1; };
template <> struct Derangements <3> { declare 2; };

template <uint N> constexpr uint d() {
	return Derangements<N>::n;
}

void statictest_d() {
	static_assert(d<1>() == 0, "");
	static_assert(d<2>() == 1, "");
	static_assert(d<3>() == 2, "");
	static_assert(d<7>() == 1854, "");
	static_assert(d<20>() == 895014631192902121, "");
}

#endif
