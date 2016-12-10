#ifndef DERANGEMENTS_HPP_Y1XK0GBZ
#define DERANGEMENTS_HPP_Y1XK0GBZ


#include "mattemp.hpp"


template <uint N> struct Derangements {
	declare(uint) (N - 1) * (Derangements<N - 1>::n + Derangements<N - 2>::n);
};
template <> struct Derangements <1> { declare(uint) 0; };
template <> struct Derangements <2> { declare(uint) 1; };
template <> struct Derangements <3> { declare(uint) 2; };


void statictest_d() {
	static_assert(Derangements<1>::n == 0, "");
	static_assert(Derangements<2>::n == 1, "");
	static_assert(Derangements<3>::n == 2, "");
	static_assert(Derangements<7>::n == 1854, "");
	static_assert(Derangements<20>::n == 895014631192902121, "");
}

#endif
