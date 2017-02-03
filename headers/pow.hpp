#ifndef POW_HPP_RUYBT7DV
#define POW_HPP_RUYBT7DV


#include "mattemp.hpp"


template <uint F, uint... Rs> struct ProductArgs {
	declare F * ProductArgs<Rs...>::n;
};
template <uint F> struct ProductArgs <F> { declare F; };



template <uint L, uint R> struct ProductRange {
	declare L * ProductRange<L + 1, R>::n;
};
template <uint L> struct ProductRange<L, L> { declare L; };


template <uint L, uint N, template <uint> class Sequence> struct SubseqProduct {
	declare Sequence<L>::n * SubseqProduct<L + 1, N - 1, Sequence>::n;
};
template <uint L, template <uint> class Sequence> struct SubseqProduct <L, 0, Sequence> {
	declare 1;
};


void statictest_product() {
	static_assert(ProductArgs<15>::n == 15, "");
	static_assert(ProductArgs<1, 2, 5, 51>::n == 510, "");
	static_assert(ProductRange<3, 3>::n == 3, "");
	static_assert(ProductRange<3, 4>::n == 12, "");
	static_assert(ProductRange<3, 5>::n == 60, "");
	static_assert(ProductRange<3, 6>::n == 360, "");
	static_assert(ProductRange<3, 10>::n == 1814400, "");
	static_assert(SubseqProduct<1, 10, Value>::n == 3628800, "");
}


template <uint N, uint P> struct Power { declare Power<N, P - 1>::n * N; };
template <uint N> struct Power <N, 0> { declare 1; };

template <uint N, uint P> constexpr uint power = Power<N, P>::n;

void statictest_pow() {
	static_assert(power<0, 0> == 1, "");
	static_assert(power<1, 0> == 1, "");
	static_assert(power<0, 1> == 0, "");
	static_assert(power<2, 3> == 8, "");
	static_assert(power<5, 6> == 15625, "");
}

#endif
