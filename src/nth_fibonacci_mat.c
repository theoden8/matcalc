#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

typedef struct _mat2 {
	mpz_t a, b, c, d;
} mat2;

void print_mat(mat2 *);
mpz_t *get_mat(mat2 *, int, int);

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

	mpz_t am, bk, an, bp, cm, dk, cn, dp;
	mpz_inits(am, bk, an, bp, cm, dk, cn, dp);
	mpz_mul(am, m->a, p->a);
	mpz_mul(bk, m->b, p->c);
	mpz_mul(an, m->a, p->b);
	mpz_mul(bp, m->b, p->d);
	mpz_mul(cm, m->c, p->a);
	mpz_mul(dk, m->d, p->c);
	mpz_mul(cn, m->c, p->b);
	mpz_mul(dp, m->d, p->d);

	mpz_add(buf->a, am, bk);
	mpz_add(buf->b, an, bp);
	mpz_add(buf->c, cm, dk);
	mpz_add(buf->d, cn, dp);
	mpz_clears(am, bk, an, bp, cm, dk, cn, dp);
}

mat2 square_mat(mat2 *m) {
	mat2 p;
	init_mat(&p);
	copy_mat(&p, m);

	mpz_t aa, ab, ac, bc, bd, cd, dd;
	mpz_inits(aa, ab, ac, bc, bd, cd, dd, NULL);

	mpz_mul(aa, m->a, m->a);
	mpz_mul(ab, m->a, m->b);
	mpz_mul(ac, m->a, m->c);
	mpz_mul(bc, m->b, m->c);
	mpz_mul(bd, m->b, m->d);
	mpz_mul(cd, m->c, m->d);
	mpz_mul(dd, m->d, m->d);

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

main(int argc, char *argv[]) {
	if(argc != 2)
		return EXIT_FAILURE;
	mat2 f;
	init_mat(&f);
	mpz_set_si(f.a, 1);
	mpz_set_si(f.b, 1);
	mpz_set_si(f.c, 1);
	mpz_set_si(f.d, 0);
	pow_mat(&f, atol(argv[1]) - 1);
	gmp_printf("%Zd\n", f.a);
	clear_mat(&f);
}
