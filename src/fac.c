#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// it is here for visual comparison with some other programs

#define ch(condition) ;if(!(condition))return EXIT_FAILURE;
#define Z(x) mpz_t x;
#define E(x) mpz_init(x);
#define B(x) mpz_fac_ui(x, n);
#define R(x) gmp_printf("%Zd\n", x);
#define A(x) mpz_clear(x);
main(int c,char**v){ch(c==2)long n=atol(v[1])ch(n>=0)Z(_)E(_)B(_)R(_)A(_)}
