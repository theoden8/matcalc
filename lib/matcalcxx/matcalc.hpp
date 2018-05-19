#pragma once

#include <matcalcxx/utils.hpp>

#include <matcalc/e_taylor.h>
#include <matcalc/pi_arctan.h>

#include <matcalc/gcd_euclid.h>
#include <matcalc/euclid.h>
#include <matcalc/erat_sieve.h>
#include <matcalc/factorization_pollard_rho.h>
#include <matcalc/nth_primorial.h>

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

namespace analysis {

using namespace util;

decltype(auto) const_e() {
  return make_scalarfr([&](mpfr_visitor vfunc) mutable -> void {
    calc_e_taylor(10000, 20000, vfunc);
  });
}

decltype(auto) const_pi() {
  return make_scalarfr([&](mpfr_visitor vfunc) mutable -> void {
    mpfr_t pi;
    mpfr_inits2(20000, pi, NULL);
    calc_pi_arctan(pi, 10000, 20000);
    vfunc(&pi);
    mpfr_clears(pi, NULL);
  });
}

namespace sequence {
} // namespace sequence

} // namespace analysis

namespace ntheory {

using namespace util;

decltype(auto) gcd(const mpz_class &a, const mpz_class &b) {
  return make_scalar([&](mpz_visitor vfunc) mutable -> void {
    calc_gcd_euclid(a.get_mpz_t(), b.get_mpz_t(), vfunc);
  });
}

decltype(auto) prime_counting(uint32_t N, EratostheneSieve &e) {
  return make_scalar_uint([=]() mutable -> uint32_t {
    e.set_size(N);
    return get_esieve_no_primes();
  });
}

decltype(auto) primorial(size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_nth_primorial(n, vfunc);
  });
}

namespace sequence {

decltype(auto) euclideans(long Q, EratostheneSieve &e) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    calc_euclid(Q, mpz_printer);
  });
}

decltype(auto) primes(uint32_t N, EratostheneSieve &e) {
  return make_prime_sequence([=](prime_visitor vfunc) mutable -> void {
    e.set_size(N);
    iter_esieve(e.get_ptr(), vfunc);
  });
}

decltype(auto) prime_factors(const mpz_class n) {
  return make_sequence([&](mpz_visitor vfunc) mutable -> void {
    calc_prime_factors_pollard_rho(n.get_mpz_t(), vfunc);
  });
}

} // namespace sequence

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

decltype(auto) c_nk(long n, long k) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_c_nk(n, k, vfunc);
  });
}

decltype(auto) derangement(size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    calc_nth_derangement(n, vfunc);
  });
}

decltype(auto) factorial(size_t n) {
  return make_scalar([=](mpz_visitor vfunc) mutable -> void {
    mpz_t f;
    mpz_init(f);
    mpz_fac_ui(f, n);
    vfunc(&f);
    mpz_clear(f);
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

decltype(auto) factorials(size_t n) {
  return make_sequence([=](mpz_visitor vfunc) mutable -> void {
    mpz_t f;
    mpz_init_set_d(f, 1);
    vfunc(&f);
    for(size_t i = 1; i <= n; ++i) {
      mpz_mul_ui(f, f, i);
      vfunc(&f);
    }
    mpz_clear(f);
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
