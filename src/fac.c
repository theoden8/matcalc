#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// it is here for visual comparison with some other programs

#define check(condition) if(!(condition))return 1;
main(int argc,char**argv){check(argc==2)long f=atol(argv[1]);check(f>=0)mpz_t fac;mpz_init(fac);mpz_fac_ui(fac, f);gmp_printf("%Zd\n", fac);mpz_clear(fac);}
