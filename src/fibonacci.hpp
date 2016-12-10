#ifndef FIBONACCI_HPP_MGJLKFSK
#define FIBONACCI_HPP_MGJLKFSK


#include "mattemp.hpp"


template <uint N> struct Fibonacci {
	declare(uint) Fibonacci<N - 2>::n + Fibonacci<N - 1>::n;
};
template <> struct Fibonacci <1> { declare(uint) 1; };
template <> struct Fibonacci <2> { declare(uint) 1; };


void statictest_fib() {
	static_assert(Fibonacci<1>::n == 1, "");
	static_assert(Fibonacci<2>::n == 1, "");
	static_assert(Fibonacci<10>::n == 55, "");
}

#endif
