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

* Wikipedia
* ITMO University wiki conspects
