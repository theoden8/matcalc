#ifndef TETRATION_HPP_R6QEBKJF
#define TETRATION_HPP_R6QEBKJF


#include "mattemp.hpp"
#include "pow.hpp"


template <uint F, uint ... Ns> struct ExponentArgs {
	declare Power<F, ExponentArgs<Ns...>::n>::n;
};
template <> struct ExponentArgs <0> { declare 0; };
template <> struct ExponentArgs <1> { declare 1; };
template <uint... Ns> struct ExponentArgs <0, Ns...> { declare ExponentArgs<0>::n; };
template <uint... Ns> struct ExponentArgs <1, Ns...> { declare ExponentArgs<1>::n; };
template <uint F> struct ExponentArgs <F> { declare F; };


void statictest_exps() {
	static_assert(ExponentArgs<10>::n == 10, "");
	static_assert(ExponentArgs<1, 2, 7, 1, 1, 1, 1>::n == 1, "");
	static_assert(ExponentArgs<1, 2, 3, 4, 5, 6, 7>::n == 1, "");
	static_assert(ExponentArgs<7, 1, 0, 4, 5, 6, 7>::n == 7, "");
	static_assert(ExponentArgs<2, 5, 1>::n == 32, "");
}


template <uint N, uint T> struct Tetration {
	declare Power<N, Tetration<N, T - 1>::n>::n;
};
template <uint N> struct Tetration <N, 0> { declare 1; };

template <uint N, uint T> constexpr uint tetration = Tetration<N, T>::n;

void statictest_tetration() {
	static_assert(tetration<2, 0> == 1, "");
	static_assert(tetration<2, 1> == 2, "");
	static_assert(tetration<2, 2> == 4, "");
	static_assert(tetration<2, 3> == 16, "");
	static_assert(tetration<2, 4> == 65536, "");
	static_assert(tetration<1, 100> == 1, "");
	static_assert(tetration<3, 2> == 27, "");
	static_assert(tetration<3, 3> == 7625597484987, "");
}


#endif
