#define declare(type) static const type n =


typedef unsigned long long uint;
typedef long long sint;


// exact same thing, but recursively and in compile time


template <class A, class B> struct Min {
	declare(uint) (A::n < B::n) ? A::n : B::n;
};
template <class A, class B> struct Max {
	declare(uint) (A::n > B::n) ? A::n : B::n;
};

template <class T, T x> struct Value {
	declare(T) x;
};


template <sint F, sint... Rs> struct ProductArgs {
	declare(sint) F * ProductArgs<Rs...>::n;
};
template <sint F> struct ProductArgs <F> { declare(sint) F; };


template <uint L, uint R> struct ProductRange {
	declare(sint) L * ProductRange<L + 1, R>::n;
};
template <uint L> struct ProductRange<L, L> { declare(sint) L; };


template <sint N, uint P> struct Power {
	declare(sint) Power<N, P - 1>::n * N;
};
template <uint N> struct Power <N, 0> { declare(sint) 1; };


template <uint N> struct Factorial {
	declare(uint) N * Factorial<N - 1>::n;
};
template <> struct Factorial <0> { declare(uint) 1; };


template <uint N, uint K> struct Binomial {
	declare(uint) Binomial<N - 1, K - 1>::n + Binomial<N - 1, K>::n;
};
template <uint N> struct Binomial <N, N> { declare(uint) 1; };
template <uint N> struct Binomial <N, 0> { declare(uint) 1; };
template <> struct Binomial <0, 0> { declare(uint) 1; };


template <uint N> struct Fibonacci {
	declare(uint) Fibonacci<N - 2>::n + Fibonacci<N - 1>::n;
};
template <> struct Fibonacci <1> { declare(uint) 1; };
template <> struct Fibonacci <2> { declare(uint) 1; };


template <uint N> struct Catalan {
	declare(uint) Binomial<2 * N, N>::n / (N + 1);
};


template <uint N> struct Derangements {
	declare(uint) (N - 1) * (Derangements<N - 1>::n + Derangements<N - 2>::n);
};
template <> struct Derangements <1> { declare(uint) 0; };
template <> struct Derangements <2> { declare(uint) 1; };
template <> struct Derangements <3> { declare(uint) 2; };


template <uint N, uint K> struct Stirling1 {
	declare(uint) Stirling1<N - 1, K - 1>::n + (N - 1)*Stirling1<N - 1, K>::n;
};
template <uint N> struct Stirling1 <N, 0> { declare(uint) 0; };
template <uint K> struct Stirling1 <0, K> { declare(uint) 0; };
template <> struct Stirling1 <0, 0> { declare(uint) 1; };


template <uint N, uint K> struct Stirling2 {
	declare(uint) (K > N) ? 0 : K * Stirling2<N - 1, K>::n + Stirling2<N - 1, K - 1>::n;
};
template <uint N> struct Stirling2 <N, 0> { declare(uint) 0; };
template <uint K> struct Stirling2 <0, K> { declare(uint) 0; };
template <uint N> struct Stirling2 <N, N> { declare(uint) 1; };
template <> struct Stirling2 <0, 0> { declare(uint) 1; };


template <uint N, uint M> struct Euler1 {
	declare(uint) (N <= M) ? 0 : (M + 1) * Euler1<N - 1, M>::n + (N - M) * Euler1<N - 1, M - 1>::n;
};
template <uint N> struct Euler1 <N, N> { declare(uint) 0; };
template <uint N> struct Euler1 <N, 0> { declare(uint) 1; };
template <> struct Euler1 <0, 0> { declare(uint) 1; };


template <uint N, uint M> struct Euler2 {
	declare(uint) (N <= M) ? 0 : (2 * N - M - 1) * Euler2<N - 1, M - 1>::n + (M + 1) * Euler2<N - 1, M>::n;
};
template <uint N> struct Euler2 <N, N> { declare(uint) 0; };
template <uint M> struct Euler2 <0, M> { declare(uint) 0; };
template <> struct Euler2 <0, 0> { declare(uint) 1; };


void check() {
	static_assert(Min<Factorial<6>, Factorial<3> >::n == Factorial<3>::n, "");
	static_assert(Max<Factorial<6>, Factorial<3> >::n == Factorial<6>::n, "");
	static_assert(ProductArgs<15>::n == 15, "");
	static_assert(ProductArgs<1, 2, -5, 51>::n == -510, "");
	static_assert(ProductRange<3, 3>::n == 3, "");
	static_assert(ProductRange<3, 4>::n == 12, "");
	static_assert(ProductRange<3, 5>::n == 60, "");
	static_assert(ProductRange<3, 6>::n == 360, "");
	static_assert(ProductRange<3, 10>::n == 1814400, "");
	static_assert(Power<0, 0>::n == 1, "");
	static_assert(Power<1, 0>::n == 1, "");
	static_assert(Power<0, 1>::n == 0, "");
	static_assert(Power<2, 3>::n == 8, "");
	static_assert(Power<5, 6>::n == 15625, "");
	static_assert(Factorial<0>::n == 1, "");
	static_assert(Factorial<5>::n == 120, "");
	static_assert(Factorial<10>::n == ProductRange<1, 10>::n, "");
	static_assert(Binomial<0, 0>::n == 1, "");
	static_assert(Binomial<9, 2>::n == 36, "");
	static_assert(Binomial<9, 7>::n == Binomial<9, 7>::n, "");
	static_assert(Binomial<20, 12>::n == 125970, "");
	static_assert(Fibonacci<1>::n == 1, "");
	static_assert(Fibonacci<2>::n == 1, "");
	static_assert(Fibonacci<10>::n == 55, "");
	static_assert(Catalan<0>::n == 1, "");
	static_assert(Catalan<1>::n == 1, "");
	static_assert(Catalan<10>::n == 16796, "");
	static_assert(Derangements<1>::n == 0, "");
	static_assert(Derangements<2>::n == 1, "");
	static_assert(Derangements<3>::n == 2, "");
	static_assert(Derangements<7>::n == 1854, "");
	static_assert(Derangements<20>::n == 895014631192902121, "");
	static_assert(Stirling1<0, 0>::n == 1, "");
	static_assert(Stirling1<3, 0>::n == 0, "");
	static_assert(Stirling1<0, 5>::n == 0, "");
	static_assert(Stirling1<6, 4>::n == 85, "");
	static_assert(Stirling1<12, 3>::n == 150917976, "");
	static_assert(Stirling2<0, 0>::n == 1, "");
	static_assert(Stirling2<5, 0>::n == 0, "");
	static_assert(Stirling2<0, 6>::n == 0, "");
	static_assert(Stirling2<5, 6>::n == 0, "");
	static_assert(Stirling2<19, 6>::n == 693081601779, "");
	static_assert(Euler1<0, 0>::n == 1, "");
	static_assert(Euler1<1, 0>::n == 1, "");
	static_assert(Euler1<2, 0>::n == 1, "");
	static_assert(Euler1<1, 1>::n == 0, "");
	static_assert(Euler1<16, 16>::n == 0, "");
	static_assert(Euler1<16, 15>::n == 1, "");
	static_assert(Euler1<15, 7>::n == 447538817472, "");
	static_assert(Euler2<0, 0>::n == 1, "");
	static_assert(Euler2<1, 0>::n == 1, "");
	static_assert(Euler2<1, 1>::n == 0, "");
	static_assert(Euler2<8, 8>::n == 0, "");
	static_assert(Euler2<9, 6>::n == 11026296, "");
}
