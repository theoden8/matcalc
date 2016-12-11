#ifndef TETRATION_HPP_R6QEBKJF
#define TETRATION_HPP_R6QEBKJF


#include "mattemp.hpp"
#include "pow.hpp"


template <uint N, uint T> struct Tetration {
	declare(uint) power<N, Tetration<N, T - 1>::n >();
};
template <uint N> struct Tetration <N, 0> { declare(uint) 1; };

template <uint N, uint T> constexpr uint tetration() {
	return Tetration<N, T>::n;
}


void statictest_tetration() {
	static_assert(tetration<2, 0>() == 1, "");
	static_assert(tetration<2, 1>() == 2, "");
	static_assert(tetration<2, 2>() == 4, "");
	static_assert(tetration<2, 3>() == 16, "");
	static_assert(tetration<2, 4>() == 65536, "");
	static_assert(tetration<1, 100>() == 1, "");
	static_assert(tetration<3, 2>() == 27, "");
	static_assert(tetration<3, 3>() == 7625597484987, "");
}


#endif
