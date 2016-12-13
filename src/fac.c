#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// it is here for visual comparison with some other programs

#define ch(condition) ;if(!(condition))return EXIT_FAILURE;
main(int c,char**v){ch(c==2)long f=atol(v[1])ch(f>=0)mpz_t fac;mpz_init(fac);mpz_fac_ui(fac, f);gmp_printf("%Zd\n", fac);mpz_clear(fac);}
