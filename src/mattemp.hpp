#ifndef MATTEMP_HPP_NMTDKPFC
#define MATTEMP_HPP_NMTDKPFC

#define declare(type) static const type n =

typedef unsigned long long uint;
typedef long long sint;


// matcalc with templates


template <class T, T x> struct Value { declare(T) x; };
template <class A, class B> struct Min { declare(uint) (A::n < B::n) ? A::n : B::n; };
template <class A, class B> struct Max { declare(uint) (A::n > B::n) ? A::n : B::n; };

template <class T, T x> constexpr T value() {
	return Value<T, x>::n;
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
}

#endif
