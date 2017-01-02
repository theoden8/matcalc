#ifndef EULER_TOTIENT_HPP_1PQCHI6A
#define EULER_TOTIENT_HPP_1PQCHI6A


#include "mattemp.hpp"
#include "gcd.hpp"


template <uint I, uint N> struct ETFLoopCoprimes {
	declare Coprime<I, N>::n + ETFLoopCoprimes<I - 1, N>::n;
};
template <uint N> struct ETFLoopCoprimes <1, N> { declare Coprime<1, N>::n; };


template <uint N> struct ETF {
	declare ETFLoopCoprimes<N - 1, N>::n;
};
template <> struct ETF <0> { declare 0; };
template <> struct ETF <1> { declare 1; };


template <uint N> superconst uint etf = ETF<N>::n;

void statictest_etf() {
	static_assert(etf<0> == 0, "");
	static_assert(etf<1> == 1, "");
	static_assert(etf<2> == 1, "");
	static_assert(etf<3> == 2, "");
	static_assert(etf<10> == 4, "");
	static_assert(etf<100> == 40, "");
}

#endif
