#ifndef HYPEROPREATION_HPP_XISXKU3L
#define HYPEROPREATION_HPP_XISXKU3L


#include "mattemp.hpp"
#include "pow.hpp"
#include "tetration.hpp"


template <muint N, muint P, template <muint, muint...> class Join> struct HyperOperation {
	declare Join<N, HyperOperation<N, P - 1, Join>::n >::n;
};
template <muint N, template <muint, muint...> class Join> struct HyperOperation <N, 0, Join> {
	declare 1;
};


void statictest_hyper() {
	static_assert(HyperOperation<2, 10, ProductArgs>::n == 1024, "");
	static_assert(HyperOperation<1, 100, ExponentArgs>::n == 1, "");
	static_assert(HyperOperation<2, 3, ExponentArgs>::n == 16, "");
}


#endif
