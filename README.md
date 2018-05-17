# matcalc

## Authors

Created by Kirill Rodriguez.

## About

This is a collection of tools useful for computing things in combinatorics, number theory, probability theory, mathematical analysis and other areas of maths.

## Goals

* Learn to work with gmp, mpfr and c++ templates.
* Explore different approaches on computing different mathematical functions faster.
* Build a low overhead API.

## Features

* Sequence generators.
* Calculations.
* Approximations.
* C++ headers with compile-time definitions.
* C++ bindings

### Keywords

* Narcissistic numbers
* Figurate numbers
* Fibonacci
* Factorial
* Factorions
* Euclidean numbers
* Binomial coefficient
* Derangements
* Catalan numbers
* Stirling numbers 1, 2
* Eulerian numbers 1, 2
* Bell numbers
* Pi digits
* E digits
* Harmonic numbers
* Natural number partition
* Ackermann
* Palindromes
* Prime sieve
* Collatz conjecture
* Polynomial coefficient
* Binomial distribution
* Poisson distribution

## Build with

* cc, c++, make, perl, bash
* gmp, mpfr, pthread, openmp, cuda

## Usage

### Compilation

	$ make

### Runing

	$ # ./bin/program ...args, e.g
	$ ./bin/erat_sieve 100000000 p | tail
 	99999839
	99999847
	99999853
	99999857
	99999901
	99999931
	99999941
	99999959
	99999971
	99999989

If you still don't understand what you see, have a look at the code, it might even have some comments in it, clarifying what is happening.

To clean up, do

	$ cd src
	$ make clean

## C++ Bindings

There is currently only one way to access a value from within a function: by implementing your own visitor function. This will be applied from within a function without waiting for it to clean up, 

```cpp
#include <matcalcxx/combinatorics.hpp>

using namespace matcalc;

void print_func(const mpz_t *x) {
	gmp_printf("%Zd\n", *x);
}

int main() {
	printf("gcd(a, b) "); ntheory::gcd(40320, 51840).print();
	printf("ack(m, n) "); combinatorics::ackermann(3, 50).print();
	printf("a1(n, m)  "); combinatorics::a_nm_1(100, 50).print();
	printf("a2(n, m)  "); combinatorics::a_nm_2(100, 50).print();
	printf("cat(n)    "); combinatorics::catalan(100).print();
	printf("c(n, k)   "); combinatorics::c_nk(100, 50).print();
	printf("d(n)      "); combinatorics::derangement(100).print();
	printf("fib(n)    "); combinatorics::fibonacci(100).print();
	printf("parttn(n) "); combinatorics::npartition(100).print();
	printf("s1(n, k)  "); combinatorics::s_nk_1(100, 50).print();
	printf("s2(n, k)  "); combinatorics::s_nk_2(100, 50).print();
	puts("\nbells");
	combinatorics::sequence::bells(20).print();
	puts("\ncatalans");
	combinatorics::sequence::catalans(20).print();
	puts("\ncollatz");
	combinatorics::sequence::collatz(20).print();
	puts("\nderangements");
	combinatorics::sequence::derangements(20).print();
	puts("\nfibonacci");
	combinatorics::sequence::fibonacci(20).visit(print_func);
	puts("\nfigurates");
	combinatorics::sequence::figurates(20, 20).visit(print_func);
}
```

Each C++ binding returns an object which can be visited, but only possesses the result after `.evaluate()` is called and until the object is destroyed.

```
gcd(a, b) 5760
ack(m, n) 1125899906842624
a1(n, m)  12626583048565731758704803903613273608195677189975104100350973856449564133356757386852425614117017819889941988926638004335803974817249421258019632694790596628
a2(n, m)  9442459110242879142255785460554415489987583780467124324883239672489226442868920997694622506743558673245459194646658362701020224959186634053798588925664046630126119147660961673904128
cat(n)    896519947090131496687170070074100632420837521538745909320
c(n, k)   100891344545564193334812497256
d(n)      34332795984163804765195977526776142032365783805375784983543400282685180793327632432791396429850988990237345920155783984828001486412574060553756854137069878601
fib(n)    31116129774182108119595549
parttn(n) 190569292
s1(n, k)  3183222782352964384744354120729686064175609439397055063717578668769227113071836382198739697421125692626030268475
s2(n, k)  430983237009366340421514301547258695943520289614340613912441741131280319058853783145598261659992013900

...
```

## Analysis tools

* Benchmarking
* Comparing output

## License

The project is licensed under [WTFPL](./LICENSE) license.

## Contributing

### Bugs and optimizations

If you find a problem, or optimization related to any of the programs/algorithms, do not hesitate posting an issue.

## Credits

* [Wikipedia](https://en.wikipedia.org/wiki/Wikipedia)
* [ITMO University wiki conspects](http://neerc.ifmo.ru/wiki/index.php?title=%D0%94%D0%B8%D1%81%D0%BA%D1%80%D0%B5%D1%82%D0%BD%D0%B0%D1%8F_%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D0%BA%D0%B0,_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B_%D0%B8_%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B_%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85)
* [Collatz conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture)