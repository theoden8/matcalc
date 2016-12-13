#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// it is here for visual comparison with some other programs

#define ch(condition) ;if(!(condition))return EXIT_FAILURE;
#define R(x) mpz_clear(x);
#define O(x) gmp_printf("%Sd\n", x);
#define T(x) mpz_fac_ui(x, n);
#define A(x) mpz_init(x);
#define S(x) mpz_t x;
main(int c,char**v){ch(c==2)long n=atol(v[1])ch(n>=0)S(_)A(_)T(_)O(_)R(_)}
