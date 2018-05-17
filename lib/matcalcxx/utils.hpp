#pragma once

#include <utility>
#include <functional>
#include <gmpxx.h>

#include <matcalc/visitor.h>

namespace matcalc {

namespace util {

template <typename F> struct Scalar;

template <typename F>
decltype(auto) make_scalar(F func) {
  return Scalar<F>(func);
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

} // namespace util
} // namespace matcalc
