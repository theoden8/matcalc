#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#include "nth_fibonacci_mat.h"

void init_mat(mat2 *m) {
	mpz_inits(m->a, m->b, m->c, m->d, NULL);
}

void identity_mat(mat2 *m) {
	mpz_set_si(m->a, 1);
	mpz_set_si(m->b, 0);
	mpz_set_si(m->c, 0);
	mpz_set_si(m->d, 1);
}

void copy_mat(mat2 *dst, mat2 *src) {
	mpz_set(dst->a, src->a);
	mpz_set(dst->b, src->b);
	mpz_set(dst->c, src->c);
	mpz_set(dst->d, src->d);
}

mpz_t *get_mat(mat2 *m, int y, int x) {
	/* return &m[y * 2 + x]; */
	switch(y * 2 + x) {
		case 0: return &m->a;
		case 1: return &m->b;
		case 2: return &m->c;
		case 3: return &m->d;
	}
	fputs("err: no such index", stderr);
	exit(1);
}

void print_mat(mat2 *m) {
	for(size_t y = 0; y < 2; ++y)
		for(size_t x = 0; x < 2; ++x)
			gmp_printf("(%d, %d) : %Zd\n", y, x, *get_mat(m, y, x));
}

void clear_mat(mat2 *m) {
	mpz_clears(m->a, m->b, m->c, m->d, NULL);
}

void mul_mat(mat2 *r, mat2 *m, mat2 *p) {
	mat2 *buf = r;

	mpz_t t1, t2, t3;
	mpz_t p1, p2, p3, p4, p5, p6, p7;

	mpz_inits(t1, t2, t3, NULL);
	mpz_inits(p1, p2, p3, p4, p5, p6, p7, NULL);
	// strassen multiplication
	#pragma omp parallel
	{
		{
			mpz_add(t1, p->a, p->d);
			mpz_add(p1, m->a, m->d);
			mpz_mul(p1, p1, t1);
		};
		{
			mpz_add(p2, m->c, m->d);
			mpz_mul(p2, p2, p->a);
		};
		{
			mpz_sub(p3, p->b, p->d);
			mpz_mul(p3, p3, p->a);
		};
		{
			mpz_sub(p4, p->c, p->a);
			mpz_mul(p4, p4, m->d);
		};
		{
			mpz_add(p5, m->a, m->b);
			mpz_mul(p5, p5, p->d);
		};
		{
			mpz_add(t2, p->a, p->b);
			mpz_sub(p6, m->c, m->a);
			mpz_mul(p6, p6, t2);
		};
		{
			mpz_add(t3, p->c, p->d);
			mpz_sub(p7, m->b, m->d);
			mpz_mul(p7, p7, t3);
		};
	}

	// result matrix
	{
		mpz_add(t1, p1, p4);
		mpz_sub(r->a, p7, p5);
		mpz_add(r->a, r->a, t1);
	};
	{
		mpz_add(r->b, p3, p5);
	};
	{
		mpz_add(r->c, p2, p4);
	};
	{
		mpz_add(t2, p1, p3);
		mpz_sub(r->d, p6, p2);
		mpz_add(r->d, r->d, t2);
	};

	mpz_clears(t1, t2, t3, NULL);

	mpz_clears(p1, p2, p3, p4, p5, p6, p7, NULL);
}

mat2 square_mat(mat2 *m) {
	mat2 p;
	init_mat(&p);
	copy_mat(&p, m);

	mpz_t aa, ab, ac, bc, bd, cd, dd;
	mpz_inits(aa, ab, ac, bc, bd, cd, dd, NULL);

	#pragma omp parallel
	{
		mpz_mul(aa, m->a, m->a);
		mpz_mul(ab, m->a, m->b);
		mpz_mul(ac, m->a, m->c);
		mpz_mul(bc, m->b, m->c);
		mpz_mul(bd, m->b, m->d);
		mpz_mul(cd, m->c, m->d);
		mpz_mul(dd, m->d, m->d);
	}

	mpz_add(p.a, aa, bc);
	mpz_add(p.b, ab, bd);
	mpz_add(p.c, ac, cd);
	mpz_add(p.d, bc, dd);

	mpz_clears(aa, ab, ac, bc, bd, cd, dd, NULL);
	clear_mat(m);

	return p;
}

void pow_mat(mat2 *m, size_t power) {
	mat2 p;
	init_mat(&p);
	copy_mat(&p, m);
	identity_mat(m);
	for(size_t i = 1; i <= power; i <<= 1) {
		if(power & i) {
			/* printf("POWER %lu\n", i); */
			/* print_mat(&p); */
			mul_mat(m, m, &p);
			/* printf("TOTAL %lu\n", i); */
			/* print_mat(m); */
		}
		p = square_mat(&p);
	}
	clear_mat(&p);
}

void calc_nth_fib_mat(size_t power) {
	mat2 f;
	init_mat(&f);
	mpz_set_si(f.a, 1);
	mpz_set_si(f.b, 1);
	mpz_set_si(f.c, 1);
	mpz_set_si(f.d, 0);
	pow_mat(&f, power);
	gmp_printf("%Zd\n", f.a);
	clear_mat(&f);
}

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	calc_nth_fib_mat(atoi(argv[1]) - 1);
}
