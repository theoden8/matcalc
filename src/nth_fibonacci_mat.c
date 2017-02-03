#include <stdlib.h>

#include <matcalc/nth_fibonacci_mat.h>

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	calc_nth_fib_mat(atoi(argv[1]) - 1);
}
