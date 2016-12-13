#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// it is here for visual comparison with some other programs

#define ch(condition) ;if(!(condition))return EXIT_FAILURE;
#define D(x) mpz_t x;
#define I(x) mpz_init(x);
#define F(x,n) mpz_fac_ui(x, n);
#define P(x) gmp_printf("%Zd\n", x);
#define C(x) mpz_clear(x);
main(int c,char**v){ch(c==2)long n=atol(v[1])ch(n>=0)D(f)I(f)F(f,n)P(f)C(f)}
