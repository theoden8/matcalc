#ifndef NTH_FIBONACCI_MAT_H_5M1IET0Z
#define NTH_FIBONACCI_MAT_H_5M1IET0Z

#include "visitor.h"

#include <stdlib.h>
#include <gmp.h>

#ifndef MAXTHREADS
#define MAXTHREADS 8
#endif

typedef struct _mat2 {
	mpz_t a, b, c, d;
} mat2;

static void print_mat(mat2 *);
static void init_mat(mat2 *m);
static void identity_mat(mat2 *m);
static void copy_mat(mat2 *dst, mat2 *src);
static mpz_t *get_mat(mat2 *, int, int);
static void print_mat(mat2 *m);
static void clear_mat(mat2 *m);
static void mul_mat(mat2 *r, mat2 *m, mat2 *p);
static mat2 square_mat(mat2 *m);
static void pow_mat(mat2 *m, size_t power);
void calc_nth_fib_mat(size_t power, mpz_visitor visitor_func);

#endif
