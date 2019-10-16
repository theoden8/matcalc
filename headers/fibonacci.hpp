#ifndef FIBONACCI_HPP_MGJLKFSK
#define FIBONACCI_HPP_MGJLKFSK


#include "mattemp.hpp"


template <muint N> struct Fibonacci {
	declare Fibonacci<N - 2>::n + Fibonacci<N - 1>::n;
};
template <> struct Fibonacci <1> { declare 1; };
template <> struct Fibonacci <2> { declare 1; };

template <muint N> superconst muint fib = Fibonacci<N>::n;

void statictest_fib() {
	static_assert(fib<1> == 1, "");
	static_assert(fib<2> == 1, "");
	static_assert(fib<10> == 55, "");
}

#endif
