#ifndef ACKERMAN_HPP_N3RY0XGW
#define ACKERMAN_HPP_N3RY0XGW


#include "mattemp.hpp"
#include "pow.hpp"


template <muint M, muint N> struct Ackermann {
	declare Ackermann<M - 1, Ackermann<M, N - 1>::n>::n;
};
/* template <muint M> struct Ackermann <M, 0> { declare Ackermann<M - 1, 1>::n;  }; */
template <muint N> struct Ackermann <0, N> { declare N + 1; };
template <muint N> struct Ackermann <1, N> { declare N + 2; };
template <muint N> struct Ackermann <2, N> { declare 2 * N + 3; };
template <muint N> struct Ackermann <3, N> { declare -3 + 8 * Power<2, N>::n; };
template <muint N> struct Ackermann <4, N> { declare Power<2, Ackermann<4, N - 1>::n + 3>::n - 3; };
template <> struct Ackermann <4, 0> { declare 13; };
template <> struct Ackermann <0, 0> { declare 1; };

template <muint M, muint N> superconst muint ack = Ackermann<M, N>::n;

void statictest_ack() {
	static_assert(ack<0, 0> == 1, "");
	static_assert(ack<1, 0> == 2, "");
	static_assert(ack<2, 0> == 3, "");
	static_assert(ack<2, 543432> == 1086867, "");
	static_assert(ack<3, 0> == 5, "");
	static_assert(ack<3, 10> == 8189, "");
	static_assert(ack<3, 15> == 262141, "");
	static_assert(ack<3, 60> == 9223372036854775805, "");
	static_assert(ack<4, 0> == 13, "");
	static_assert(ack<4, 1> == 65533, "");
}

#endif
