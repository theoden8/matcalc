#ifndef MATTEMP_HPP_NMTDKPFC
#define MATTEMP_HPP_NMTDKPFC

#include <cstdint>
#include <cstdlib>

// matcalc in compile time

#define superconst const constexpr
#define declare static superconst muint n =
#define redeclare static superconst real n =

typedef uint64_t muint;
typedef long long sint;
typedef long double real;

template <muint N> struct Value { declare N; };
template <muint N, muint D> struct Fraction {
	superconst static auto _n = N, _d = D;
	redeclare real(N) / real(D);
};
template <class A, class B> struct Min { declare (A::n < B::n) ? A::n : B::n; };
template <class A, class B> struct Max { declare (A::n > B::n) ? A::n : B::n; };

template <muint N> constexpr muint value() {
	return N;
}

template <muint N, muint D> constexpr real frac() {
	return Fraction<N, D>::n;
}

template <class A, class B> constexpr muint mmin() {
	return Min<A, B>::n;
}

template <class A, class B> constexpr muint mmax() {
	return Max<A, B>::n;
}


void statictest() {
	static_assert(mmin<Value<6>, Value<3> >() == 3, "");
	static_assert(mmax<Value<6>, Value<3> >() == 6, "");
	static_assert(value<1323>() == 1323, "");
	static_assert(frac<1, 2>() == .5, "");
	static_assert(frac<10, 10>() == 1., "");
}

#endif
