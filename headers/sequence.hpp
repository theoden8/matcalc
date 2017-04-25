#ifndef SEQUENCE_HPP_FT5W9WOK
#define SEQUENCE_HPP_FT5W9WOK


#include <utility>
#include "mattemp.hpp"


template <uint F, uint... Rs> struct SumArgs {
	declare F + SumArgs<Rs...>::n;
};
template <uint F> struct SumArgs <F> { declare F; };

template <uint L, uint N, template <uint> class Sequence> struct SubseqSum {
	declare Sequence<L>::n + SubseqSum<L + 1, N - 1, Sequence>::n;
};
template <uint L, template <uint> class Sequence> struct SubseqSum <L, 0, Sequence> {
	declare 0;
};

void statictest_sum() {
	static_assert(SumArgs<1, 2, 3, 4>::n == 10, "");
	static_assert(SumArgs<0, 0, 14, 54, 12>::n == 80, "");
	static_assert(SubseqSum<95, 11, Value>::n == 1100, "");
}


// "array"
template <size_t... Ns>
using to_sequence = std::integer_sequence<size_t, Ns...>;

//is same
template <class A, class B> struct issame {
	static const bool value = false;
};
template <class A> struct issame <A, A> {
	static const bool value = true;
};

// len
template <class A> struct len_struct;
template <size_t... Ns>
struct len_struct <to_sequence<Ns...> > {
	static const size_t value = sizeof...(Ns);
};

template <size_t... Ns>
using len = len_struct<to_sequence<Ns...> >;

// head
template <class A> struct head_struct;
template <size_t F, size_t... Ns>
struct head_struct <to_sequence<F, Ns...> > {
	static const size_t value = F;
};
template <>
struct head_struct<to_sequence<> > {
};

template <size_t... Ns>
using head = head_struct<to_sequence<Ns...> >;

// last
template <class A> struct last_struct;
template <size_t F, size_t... Ns>
struct last_struct <to_sequence<F, Ns...> > {
	static const size_t value = last_struct<to_sequence<Ns...> >::value;
};

template <size_t F>
struct last_struct <to_sequence<F> > {
	static const size_t value = F;
};

template <size_t... Ns>
using last = last_struct<to_sequence<Ns...> >;

// concat
template <class A, class B> struct concat;
template <size_t... As, size_t... Bs>
struct concat <to_sequence<As...>, to_sequence<Bs...> > {
	using type = to_sequence<As..., Bs...>;
};

// tail
template <class A> struct tailstruct;
template <size_t F, size_t... Ns> struct tailstruct <to_sequence<F, Ns...> > {
	using type = to_sequence<Ns...>;
};
template <> struct tailstruct <to_sequence<> > {
	using type = to_sequence<>;
};
template <size_t... Ns>
using tail = typename tailstruct<to_sequence<Ns...> >::type;

// init
template <class N> struct initial;
template <size_t F, size_t... Ns>
struct initial <to_sequence<F, Ns...> > {
	using type = typename concat<to_sequence<F>, typename initial<to_sequence<Ns...> >::type >::type;
};
template <size_t F>
struct initial<to_sequence<F> > {
	using type = to_sequence<>;
};
template <>
struct initial <to_sequence<> > {
	using type = to_sequence<>;
};
template <size_t... Ns>
using init = typename initial<to_sequence<Ns...> >::type;

// reverse
template <class N> struct reverse;
template <size_t F, size_t... Ns>
struct reverse <to_sequence<F, Ns...> > {
	using type = typename concat<typename reverse<to_sequence<Ns...> >::type, to_sequence<F> >::type;
};
template <>
struct reverse <to_sequence<> > {
	using type = to_sequence<>;
};

template <size_t... Ns>
using rev = typename reverse<to_sequence<Ns...> >::type;

// take
template <size_t N, class A> struct take_n;
template <size_t N, size_t F, size_t... As>
struct take_n <N, to_sequence<F, As...> > {
	using type = typename concat<to_sequence<F>, typename take_n<N - 1, to_sequence<As...> >::type>::type;
};
template <size_t N>
struct take_n <N, to_sequence<> > {
	using type = to_sequence<>;
};
template <size_t F, size_t... Ns>
struct take_n <0, to_sequence<F, Ns...> > {
	using type = to_sequence<>;
};
template <>
struct take_n<0, to_sequence<> > {
	using type = to_sequence<>;
};
template <size_t N, size_t... Ns>
using take = typename take_n<N, to_sequence<Ns...> >::type;

// drop
template <size_t N, class A> struct drop_n;
template <size_t N, size_t F, size_t... As>
struct drop_n<N, to_sequence<F, As...> > {
	using type = typename drop_n<N - 1, to_sequence<As...> >::type;
};
template <size_t N>
struct drop_n<N, to_sequence<> > {
	using type = to_sequence<>;
};
template <size_t F, size_t... As>
struct drop_n<0, to_sequence<F, As...> > {
	using type = to_sequence<F, As...>;
};
template <size_t N, size_t... Ns>
using drop = typename drop_n<N, to_sequence<Ns...> >::type;

// msort
template <class A, class B> struct mergewrap;
template <class A, class B, class CMP = std::integral_constant<bool, (head_struct<A>::value < head_struct<B>::value)> > struct merge;
template <class A> struct msort;

template <size_t... Xs, size_t... Ys>
struct mergewrap <to_sequence<Xs...>, to_sequence<Ys...> > {
	using type = typename merge <to_sequence<Xs...>, to_sequence<Ys...> > :: type;
};
template <size_t... Xs>
struct mergewrap <to_sequence<Xs...>, to_sequence<> > {
	using type = to_sequence<Xs...>;
};
template <size_t... Ys>
struct mergewrap <to_sequence<>, to_sequence<Ys...> > {
	using type = to_sequence<Ys...>;
};
template <>
struct mergewrap <to_sequence<>, to_sequence<> > {
	using type = to_sequence<>;
};

template <size_t X, size_t... Xs, size_t Y, size_t... Ys>
struct merge <to_sequence<X, Xs...>, to_sequence<Y, Ys...>, std::integral_constant<bool, true> > {
	using type = typename concat <to_sequence<X>, typename mergewrap<to_sequence<Xs...>, to_sequence<Y, Ys...> >::type >::type;
};
template <size_t X, size_t... Xs, size_t Y, size_t... Ys>
struct merge <to_sequence<X, Xs...>, to_sequence<Y, Ys...>, std::integral_constant<bool, false> > {
	using type = typename concat <to_sequence<Y>, typename mergewrap<to_sequence<X, Xs...>, to_sequence<Ys...> >::type >::type;
};

template <size_t... Ns> struct msort <to_sequence<Ns...> > {
private:
	static const size_t mid = len<Ns...>::value >> 1;
public:
	using type = typename mergewrap <
		typename msort <take <mid, Ns...> >::type,
		typename msort <drop <mid, Ns...> >::type
	>::type;
};
template <size_t X> struct msort <to_sequence<X> > {
	using type = to_sequence<X>;
};
template <> struct msort <to_sequence<> > {
	using type = to_sequence<>;
};

template <size_t... Ns>
using tempsort = typename msort<to_sequence<Ns...> >::type;

void statictest_sequence() {
	// len, basic, head
	static_assert(len<1, 2, 3, 4>::value == 4, "");
	static_assert(head<1, 2, 3, 4>::value == 1, "");
	static_assert(last<1, 2, 3, 4>::value == 4, "");
	//concat
	static_assert(issame<typename concat<to_sequence<>, to_sequence<1> >::type, to_sequence<1> >::value, "");
	static_assert(issame<typename concat<to_sequence<1, 2, 3>, to_sequence<> >::type, to_sequence<1, 2, 3> >::value, "");
	static_assert(issame<typename concat<to_sequence<1,2,3>, to_sequence<4,5,6> >::type, to_sequence<1,2,3,4,5,6> >::value, "");
	//tail
	static_assert(issame<tail<>, to_sequence<> >::value, "");
	static_assert(issame<tail<1>, to_sequence<> >::value, "");
	static_assert(issame<tail<1,2>, to_sequence<2> >::value, "");
	static_assert(issame<tail<1,2,3,4,5,6>, to_sequence<2,3,4,5,6> >::value, "");
	//init
	static_assert(issame<init<>, to_sequence<> >::value, "");
	static_assert(issame<init<1>, to_sequence<> >::value, "");
	static_assert(issame<init<1,2>, to_sequence<1> >::value, "");
	static_assert(issame<init<1,2,3,4,5,6>, to_sequence<1,2,3,4,5> >::value, "");
	//reverse
	static_assert(issame<rev<>, to_sequence<> >::value, "");
	static_assert(issame<rev<1>, to_sequence<1> >::value, "");
	static_assert(issame<rev<1,2>, to_sequence<2,1> >::value, "");
	static_assert(issame<rev<1,2,3,4,5,6>, to_sequence<6,5,4,3,2,1> >::value, "");
	//take
	static_assert(issame<take<0>, to_sequence<> >::value, "");
	static_assert(issame<take<0, 1,2,3,4,5,6>, to_sequence<> >::value, "");
	static_assert(issame<take<10, 1,2,3,4,5,6>, to_sequence<1,2,3,4,5,6> >::value, "");
	static_assert(issame<take<2, 1,2,3,4,5,6>, to_sequence<1,2> >::value, "");
	//drop
	static_assert(issame<drop<0>, to_sequence<> >::value, "");
	static_assert(issame<drop<0, 1,2,3,4,5>, to_sequence<1,2,3,4,5> >::value, "");
	static_assert(issame<drop<1, 1>, to_sequence<> >::value, "");
	static_assert(issame<drop<2, 1,2,3>, to_sequence<3> >::value, "");
	static_assert(issame<drop<2, 1,2,3,4,5,6>, to_sequence<3,4,5,6> >::value, "");
	//tempsort
	static_assert(issame<tempsort<>, to_sequence<> >::value, "");
	static_assert(issame<tempsort<1>, to_sequence<1> >::value, "");
	static_assert(issame<tempsort<1,2>, to_sequence<1,2> >::value, "");
	static_assert(issame<tempsort<1,2,3>, to_sequence<1,2,3> >::value, "");
	static_assert(issame<tempsort<18,10,15,25,5,41,50,71,32,41>, to_sequence<5,10,15,18,25,32,41,41,50,71> >::value, "");
}

#endif
