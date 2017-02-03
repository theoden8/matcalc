#ifndef SEQUENCE_HPP_FT5W9WOK
#define SEQUENCE_HPP_FT5W9WOK


#include "mattemp.hpp"


template <uint F, uint... Rs> struct SumArgs {
	declare F + SumArgs<Rs...>::n;
};
template <uint F> struct SumArgs <F> { declare F; };

template <uint L, uint N, template <uint> class Sequence> struct SubseqSum {
	declare Sequence<L>::n + SubseqSum<L + 1, N - 1, Sequence>::n;
};
template <uint L, template <uint> class Sequence> struct SubseqSum <L, 0, Sequence> {
	declare 0;
};

void statictest_sum() {
	static_assert(SumArgs<1, 2, 3, 4>::n == 10, "");
	static_assert(SumArgs<0, 0, 14, 54, 12>::n == 80, "");
	static_assert(SubseqSum<95, 11, Value>::n == 1100, "");
}

#endif
