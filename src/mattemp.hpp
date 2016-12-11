#ifndef MATTEMP_HPP_NMTDKPFC
#define MATTEMP_HPP_NMTDKPFC

// matcalc in compile time

#define declare static const auto n =
#define redeclare constexpr declare

typedef unsigned long long uint;
typedef long long sint;
typedef long double real;

template <class T, T x> struct Value { declare x; };
template <uint N, uint D> struct Fraction {
	const static auto _n = N, _d = D;
	redeclare real(N) / real(D);
};
template <class A, class B> struct Min { declare (A::n < B::n) ? A::n : B::n; };
template <class A, class B> struct Max { declare (A::n > B::n) ? A::n : B::n; };

template <class T, T x> constexpr T value() {
	return Value<T, x>::n;
}

template <uint N, uint D> constexpr real frac() {
	return Fraction<N, D>::n;
}

template <class A, class B> constexpr uint mmin() {
	return Min<A, B>::n;
}

template <class A, class B> constexpr uint mmax() {
	return Max<A, B>::n;
}


void statictest() {
	static_assert(mmin<Value<uint, 6>, Value<uint, 3> >() == value<uint, 3>(), "");
	static_assert(mmax<Value<uint, 6>, Value<uint, 3> >() == value<uint, 6>(), "");
	static_assert(value<uint, 1323>() == 1323, "");
	static_assert(frac<1, 2>() == .5, "");
	static_assert(frac<10, 10>() == 1., "");
}

#endif
