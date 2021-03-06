#include <matcalcxx/matcalc.hpp>

using namespace matcalc;

void print_func(const mpz_t *x) {
  gmp_printf("%Zd\n", *x);
}

int main() {
  EratostheneSieve e;
  printf("ack(m, n) "); combinatorics::ackermann(3, 50).print();
  printf("a1(n, m)  "); combinatorics::a_nm_1(100, 50).print();
  printf("a2(n, m)  "); combinatorics::a_nm_2(100, 50).print();
  printf("cat(n)    "); combinatorics::catalan(100).print();
  printf("c(n, k)   "); combinatorics::c_nk(100, 50).print();
  printf("d(n)      "); combinatorics::derangement(100).print();
  printf("fac(n)    "); combinatorics::factorial(100).print();
  printf("fib(n)    "); combinatorics::fibonacci(100).print();
  printf("parttn(n) "); combinatorics::npartition(100).print();
  printf("s1(n, k)  "); combinatorics::s_nk_1(100, 50).print();
  printf("s2(n, k)  "); combinatorics::s_nk_2(100, 50).print();
  printf("gcd(a, b) "); ntheory::gcd(40320, 51840).print();
  printf("pcount(n) "); ntheory::prime_counting(10000, e).print();
  printf("n#(n)     "); ntheory::primorial(100).print();
  printf("~e:       "); analysis::const_e().print();
  printf("~pi:      "); analysis::const_pi().print();
  printf("~fib(n):  "); analysis::fibonacci(100).print();
  /* auto a = combinatorics::s_nk_1(100, 50); */
  /* auto b = combinatorics::s_nk_2(100, 50); */
  /* auto c = a + b; */
  puts("\nbells");
  combinatorics::sequence::bells(20).print();
  puts("\ncatalans");
  combinatorics::sequence::catalans(20).print();
  puts("\ncollatz");
  combinatorics::sequence::collatz(20).print();
  puts("\nderangements");
  combinatorics::sequence::derangements(20).print();
  puts("\nfactorials");
  combinatorics::sequence::factorials(20).visit(print_func);
  puts("\nfibonacci");
  combinatorics::sequence::fibonacci(20).visit(print_func);
  puts("\nfigurates");
  combinatorics::sequence::figurates(20, 20).visit(print_func);
  puts("\neuclideans");
  ntheory::sequence::euclideans(20, e).print();
  puts("\nprimes");
  ntheory::sequence::primes(100, e).print();
  puts("\nprime_factors");
  ntheory::sequence::prime_factors(mpz_class("128387568424628448")).print();
}
