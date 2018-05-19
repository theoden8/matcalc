#pragma once

#include <utility>
#include <functional>
#include <gmpxx.h>

#include <matcalc/erat_sieve.h>
#include <matcalc/visitor.h>
#include <matcalc/probability.h>

namespace matcalc {

namespace util {

template <typename F> struct Scalar;

template <typename F>
decltype(auto) make_scalar(F func) {
  return Scalar<decltype(func)>(func);
}

// f :: mpz_visitor -> void

template <typename F>
struct Scalar {
  using This = Scalar<F>;

  F func;
  Scalar(F func):
    func(func)
  {
    mpz_init(v);
    mpz_set_d(v, 0);
  }

  static mpz_t v;
  static void assign(mpz_t *z) {
    mpz_set(v, *z);
  }

/*   operator mpz_class() { */
/*     evaluate(); */
/*     return mpz_class(This::v); */
/*   } */

  auto evaluate() {
    static bool is_evaluated = false;
    if(!is_evaluated) {
      func(assign);
    }
    return This::v;
  }

/*   template <typename FF> */
/*   decltype(auto) operator+(Scalar<FF> &scal) { */
/*     return make_scalar([&](mpz_visitor vfunc) mutable -> void { */
/*       mpz_t z; */
/*       mpz_init(z); */
/*       mpz_add(z, evaluate(), scal.evaluate()); */
/*       vfunc(&z); */
/*       mpz_clear(z); */
/*     }); */
/*   } */

/*   template <typename FF> */
/*   decltype(auto) operator-(Scalar<FF> &scal) { */
/*     return make_scalar([&](mpz_visitor vfunc) mutable -> void { */
/*       mpz_t z; */
/*       mpz_init(z); */
/*       mpz_sub(z, evaluate(), scal.evaluate()); */
/*       vfunc(&z); */
/*       mpz_clear(z); */
/*     }); */
/*   } */

/*   template <typename FF> */
/*   decltype(auto) operator*(Scalar<FF> &scal) { */
/*     return make_scalar([&](mpz_visitor vfunc) mutable -> void { */
/*       evaluate(); */
/*       scal.evaluate(); */
/*       mpz_t z; */
/*       mpz_init(z); */
/*       mpz_mul(z, evaluate(), scal.evaluate()); */
/*       vfunc(&z); */
/*       mpz_clear(z); */
/*     }); */
/*   } */

  ~Scalar() {
    mpz_clear(v);
  }

  void visit(mpz_visitor vfunc) {
    func(vfunc);
  }

  void print() {
    func(mpz_printer);
  }
};

template <typename F> mpz_t Scalar<F>::v;

template <typename F> struct ScalarUint;
template <typename F> decltype(auto) make_scalar_uint(F func) { return ScalarUint<F>(func); }
template <typename F> struct ScalarUint {
  F func;
  ScalarUint(F func):func(func){}

  size_t val = ~size_t(0);

  auto evaluate() {
    if(val == ~size_t(0)) {
      val = func();
    }
    return val;
  }

  template <typename Callable>
  void visit(Callable c) {
    c(evaluate());
  }

  void print() {
    printf("%lu\n", evaluate());
  }
};

template <typename F> struct ScalarFR;

template <typename F> decltype(auto) make_scalarfr(F func) { return ScalarFR<F>(func); }

template <typename F>
struct ScalarFR {
  F func;
  ScalarFR(F func):
    func(func)
  {
    mpfr_inits2(PRECISION, v, NULL);
    mpfr_set_si(v, 0, MPFR_RNDN);
  }

  static mpfr_t v;
  static void assign(mpfr_t *z) {
    mpfr_set(v, *z, MPFR_RNDN);
  }

  ~ScalarFR() {
    mpfr_clear(v);
  }

  void visit(mpz_visitor vfunc) {
    func(vfunc);
  }

  void print() {
    func(mpfr_printer);
  }
};

template <typename F> mpfr_t ScalarFR<F>::v;


template <typename F> struct Sequence;
template <typename F> decltype(auto) make_sequence(F func) {
  return Sequence<F>(func);
}
template <typename F> struct Sequence {
  F func;

  Sequence(F func):
    func(func)
  {}

  void visit(mpz_visitor vfunc) {
    func(vfunc);
  }

  void print() {
    func(mpz_printer);
  }
};


template <typename F> struct PrimeSequence;

template <typename F>
decltype(auto) make_prime_sequence(F func) {
  return PrimeSequence<F>(func);
}

template <typename F>
struct PrimeSequence {
  F func;
  PrimeSequence(F func):
    func(func)
  {}

  void visit(prime_visitor vfunc) {
    func(vfunc);
  }

  void print() {
    func(prime_printer);
  }
};

} // namespace util
} // namespace matcalc

class EratostheneSieve {
  esieve_t *e = nullptr;
public:

  EratostheneSieve(uint N=E_CURRENT):
    e(get_esieve(N))
  {}

  void set_size(uint N) {
    e = get_esieve(N);
  }

  const esieve_t *get_ptr() {
    return e;
  }

  ~EratostheneSieve() {
    e = get_esieve(E_UNDEFINED);
  }

  decltype(auto) operator=(const EratostheneSieve) = delete;
};
