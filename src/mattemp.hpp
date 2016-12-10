#ifndef MATTEMP_HPP_NMTDKPFC
#define MATTEMP_HPP_NMTDKPFC

#define declare(type) static const type n =

typedef unsigned long long uint;
typedef long long sint;


// matcalc with templates


template <class T, T x> struct Value { declare(T) x; };
template <class A, class B> struct Min { declare(uint) (A::n < B::n) ? A::n : B::n; };
template <class A, class B> struct Max { declare(uint) (A::n > B::n) ? A::n : B::n; };


void statictest() {
	static_assert(Min<Value<uint, 6>, Value<uint, 3> >::n == Value<uint, 3>::n, "");
	static_assert(Max<Value<uint, 6>, Value<uint, 3> >::n == Value<uint, 6>::n, "");
	static_assert(Value<uint, 1323>::n == 1323, "");
}

#endif
