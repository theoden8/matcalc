#pragma once

#include <matcalcxx/utils.hpp>

#include <matcalc/gcd_euclid.h>

#include <matcalc/ackermann.h>
#include <matcalc/a_nm_1.h>
#include <matcalc/a_nm_2.h>
#include <matcalc/nth_catalan.h>
#include <matcalc/nth_derangements.h>
#include <matcalc/n_partition.h>
#include <matcalc/catalans.h>
#include <matcalc/nth_derangements.h>
#include <matcalc/nth_fibonacci_mat.h>
#include <matcalc/c_nk.h>
#include <matcalc/s_nk_1.h>
#include <matcalc/s_nk_2.h>

#include <matcalc/bells.h>
#include <matcalc/catalans.h>
#include <matcalc/collatz.h>
#include <matcalc/derangements.h>
#include <matcalc/fibonacci.h>
#include <matcalc/figurate.h>

namespace matcalc {

namespace ntheory {

using namespace util;

decltype(auto) gcd(const mpz_class &a, const mpz_class &b) {
  return make_scalar([&](mpz_visitor vfunc) mutable -> void {
    calc_gcd_euclid(a.get_mpz_t(), b.get_mpz_t(), vfunc);
  });
}

} // namespace ntheory

namespace combinatorics {

using namespace util;

decltype(auto) ackermann(size_t m, size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_ackermann(m, n, vfunc);
  });
}

decltype(auto) a_nm_1(size_t n, size_t m) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_anm1(n, m, vfunc);
  });
}

decltype(auto) a_nm_2(size_t n, size_t m) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_anm2(n, m, vfunc);
  });
}

decltype(auto) catalan(size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_nth_catalan(n, vfunc);
  });
}

decltype(auto) c_nk(size_t n, size_t k) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_c_nk(n, k, vfunc);
  });
}

decltype(auto) derangement(size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_nth_derangement(n, vfunc);
  });
}

decltype(auto) fibonacci(size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_nth_fib_mat(n, vfunc);
  });
}

decltype(auto) npartition(size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_npartition(n, vfunc);
  });
}

decltype(auto) s_nk_1(size_t n, size_t k) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_snk1(n, k, vfunc);
  });
}

decltype(auto) s_nk_2(size_t n, size_t k) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_snk2(n, k, vfunc);
  });
}

namespace sequence {

decltype(auto) bells(size_t n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    calc_bells(n, vfunc);
  });
}

decltype(auto) catalans(size_t n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    calc_catalans(n, vfunc);
  });
}

decltype(auto) collatz(mpz_t n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    calc_collatz_convergence(n, vfunc);
  });
}

decltype(auto) collatz(size_t n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    mpz_t z;
    mpz_init(z);
    mpz_set_d(z, n);
    calc_collatz_convergence(z, vfunc);
    mpz_clear(z);
  });
}

decltype(auto) derangements(long n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    calc_derangements(n, vfunc);
  });
}

decltype(auto) fibonacci(size_t n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    calc_fibs(n, vfunc);
  });
}

decltype(auto) figurates(size_t k, size_t n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    calc_figurate(k, n, vfunc);
  });
}

} // namespace sequence

} // namespace combinatorics
} // namespace matcalc
