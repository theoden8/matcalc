#ifndef HYPEROPREATION_HPP_XISXKU3L
#define HYPEROPREATION_HPP_XISXKU3L


#include "mattemp.hpp"
#include "pow.hpp"
#include "tetration.hpp"


template <uint N, uint P, template <uint, uint...> class Join> struct HyperOperation {
	declare(uint) Join<N, HyperOperation<N, P - 1, Join>::n >::n;
};
template <uint N, template <uint, uint...> class Join> struct HyperOperation <N, 0, Join> {
	declare(uint) 1;
};


void statictest_hyper() {
	static_assert(HyperOperation<2, 10, ProductArgs>::n == 1024, "");
	static_assert(HyperOperation<1, 100, ExponentArgs>::n == 1, "");
	static_assert(HyperOperation<2, 3, ExponentArgs>::n == 16, "");
}


#endif
