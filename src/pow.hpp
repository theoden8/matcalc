#ifndef POW_HPP_RUYBT7DV
#define POW_HPP_RUYBT7DV


#include "mattemp.hpp"

template <sint F, sint... Rs> struct ProductArgs {
	declare(sint) F * ProductArgs<Rs...>::n;
};
template <sint F> struct ProductArgs <F> { declare(sint) F; };



template <uint L, uint R> struct ProductRange {
	declare(sint) L * ProductRange<L + 1, R>::n;
};
template <uint L> struct ProductRange<L, L> { declare(sint) L; };

void statictest_product() {
	static_assert(ProductArgs<15>::n == 15, "");
	static_assert(ProductArgs<1, 2, -5, 51>::n == -510, "");
	static_assert(ProductRange<3, 3>::n == 3, "");
	static_assert(ProductRange<3, 4>::n == 12, "");
	static_assert(ProductRange<3, 5>::n == 60, "");
	static_assert(ProductRange<3, 6>::n == 360, "");
	static_assert(ProductRange<3, 10>::n == 1814400, "");
}


template <sint N, uint P> struct Power { declare(sint) Power<N, P - 1>::n * N; };
template <uint N> struct Power <N, 0> { declare(sint) 1; };

template <uint N, uint P> constexpr uint power() {
	return Power<N, P>::n;
}

void statictest_pow() {
	static_assert(power<0, 0>() == 1, "");
	static_assert(power<1, 0>() == 1, "");
	static_assert(power<0, 1>() == 0, "");
	static_assert(power<2, 3>() == 8, "");
	static_assert(power<5, 6>() == 15625, "");
}

#endif
