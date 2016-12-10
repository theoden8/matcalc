#ifndef FIBONACCI_HPP_MGJLKFSK
#define FIBONACCI_HPP_MGJLKFSK


#include "mattemp.hpp"


template <uint N> struct Fibonacci {
	declare(uint) Fibonacci<N - 2>::n + Fibonacci<N - 1>::n;
};
template <> struct Fibonacci <1> { declare(uint) 1; };
template <> struct Fibonacci <2> { declare(uint) 1; };

template <uint N> constexpr uint fib() {
	return Fibonacci<N>::n;
}

void statictest_fib() {
	static_assert(fib<1>() == 1, "");
	static_assert(fib<2>() == 1, "");
	static_assert(fib<10>() == 55, "");
}

#endif
