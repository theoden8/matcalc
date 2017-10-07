#ifndef GCD_HPP_RGTDCF9S
#define GCD_HPP_RGTDCF9S


#include "mattemp.hpp"


template <uint A, uint B> struct GCD {
	declare (A > B) ? GCD<A % B, B>::n : (A < B) ? GCD<A, B % A>::n : A;
};
template <uint A> struct GCD <A, 0> { declare A; };
template <uint B> struct GCD <0, B> { declare B; };

template <uint A, uint B> superconst uint gcd = GCD<A, B>::n;


void statictest_gcd() {
	static_assert(gcd<1, 1> == 1, "");
	static_assert(gcd<5, 1> == 1, "");
	static_assert(gcd<5, 2> == 1, "");
	static_assert(gcd<5, 5> == 5, "");
	static_assert(gcd<1001, 143> == 143, "");
	static_assert(gcd<700, 0> == 700, "");
	static_assert(gcd<0, 700> == 700, "");
	static_assert(gcd<99999999, 100000000> == 1, "");
}

template <uint A, uint B> struct Coprime { declare (GCD<A, B>::n == 1) ? 1 : 0; };

void statictest_coprime() {
	static_assert(Coprime<1, 1>::n == 1, "");
	static_assert(Coprime<0, 1>::n == 1, "");
	static_assert(Coprime<123, 321>::n == 0, "");
	static_assert(Coprime<1234, 4321>::n == 1, "");
}

#endif