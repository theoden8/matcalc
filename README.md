# matcalc

## Authors

Created by Kirill Rodriguez in 2016/08.

## About

This is a collection of tools useful for combinatorics, number theory and other areas of maths.

## Goals

* Learn to work with gmp, mpfr and c++ templates.
* Explore different approaches on computing different mathematical functions faster.

## Features

* Sequence generators.
* Calculations.
* Approximations.
* C++ headers with compile-time definitions.

### Keywords

* Narcissistic numbers
* Figurate numbers
* Fibonacci
* Factorial
* Factorions
* Euclidean numbers
* Binomial coefficient
* Derangements
* Catalan
* Stirling 1, 2
* Eulerian 1, 2
* Pi digits
* E digits
* Harmonic numbers
* Natural number partition
* Ackermann
* Palindromes
* Prime sieve
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

## License

The project is licensed under [WTFPL](./LICENSE) license.

## Analysis tools

* Benchmarking
* Comparing output

## Contributing

### Bugs and optimizations

If you find a problem, or optimization related to any of the programs/algorithms, do not hesitate posting an issue.

## Credits

* [Wikipedia](https://en.wikipedia.org/wiki/Wikipedia)
* [ITMO University wiki conspects](http://neerc.ifmo.ru/wiki/index.php?title=%D0%94%D0%B8%D1%81%D0%BA%D1%80%D0%B5%D1%82%D0%BD%D0%B0%D1%8F_%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D0%BA%D0%B0,_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B_%D0%B8_%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B_%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85)
