#ifndef NTH_FIBONACCI_MAT_H_5M1IET0Z
#define NTH_FIBONACCI_MAT_H_5M1IET0Z

#include <gmp.h>

typedef struct _mat2 {
	mpz_t a, b, c, d;
} mat2;

void print_mat(mat2 *);
void init_mat(mat2 *m);
void identity_mat(mat2 *m);
void copy_mat(mat2 *dst, mat2 *src);
mpz_t *get_mat(mat2 *, int, int);
void print_mat(mat2 *m);
void clear_mat(mat2 *m);
void mul_mat(mat2 *r, mat2 *m, mat2 *p);
mat2 square_mat(mat2 *m);
void pow_mat(mat2 *m, size_t power);
void calc_nth_fib_mat(size_t power);

#endif
