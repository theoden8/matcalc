#ifndef EULER_TOTIENT_HPP_1PQCHI6A
#define EULER_TOTIENT_HPP_1PQCHI6A


#include "mattemp.hpp"
#include "gcd.hpp"


template <muint I, muint N> struct ETFLoopCoprimes {
	declare Coprime<I, N>::n + ETFLoopCoprimes<I - 1, N>::n;
};
template <muint N> struct ETFLoopCoprimes <1, N> { declare Coprime<1, N>::n; };


template <muint N> struct ETF {
	declare ETFLoopCoprimes<N - 1, N>::n;
};
template <> struct ETF <1> { declare 1; };


template <muint N> superconst muint etf = ETF<N>::n;

void statictest_etf() {
	static_assert(etf<1> == 1, "");
	static_assert(etf<2> == 1, "");
	static_assert(etf<3> == 2, "");
	static_assert(etf<10> == 4, "");
	static_assert(etf<100> == 40, "");
}

#endif
