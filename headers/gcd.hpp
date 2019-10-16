#ifndef GCD_HPP_RGTDCF9S
#define GCD_HPP_RGTDCF9S


#include "mattemp.hpp"


namespace detail {

template <muint A, muint B> struct cmp_struct {
	static constexpr int n = (A > B) ? 1 : (A == B) ? 0 : -1;
};

template <muint A, muint B, int cmp = cmp_struct<A, B>::n> struct gcd_struct;

template <muint A, muint B> struct gcd_struct <A, B, 1> { declare gcd_struct<A % B, B>::n; };
template <muint A, muint B> struct gcd_struct <A, B, 0> { declare A; };
template <muint A, muint B> struct gcd_struct <A, B, -1> { declare gcd_struct<A, B % A>::n; };
template <muint A> struct gcd_struct<A, 0, 1> { declare A; };
template <muint A> struct gcd_struct<A, 0, 0> { declare A; };
template <muint B> struct gcd_struct<0, B, -1> { declare B; };
template <muint B> struct gcd_struct<0, B, 0> { declare B; };

} // namespace detail

template <muint A, muint B> struct GCD {
	declare detail::gcd_struct<A, B>::n;
};
template <muint A, muint B> superconst muint gcd = GCD<A, B>::n;


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

template <muint A, muint B> struct Coprime { declare (GCD<A, B>::n == 1) ? 1 : 0; };

void statictest_coprime() {
	static_assert(Coprime<1, 1>::n == 1, "");
	static_assert(Coprime<0, 1>::n == 1, "");
	static_assert(Coprime<123, 321>::n == 0, "");
	static_assert(Coprime<1234, 4321>::n == 1, "");
}

#endif
