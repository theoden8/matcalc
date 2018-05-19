#ifndef E_TAYLOR_H_AFVLGOWU
#define E_TAYLOR_H_AFVLGOWU

#include "visitor.h"

#include <mpfr.h>

void calc_e_taylor(int niters, int prec, mpfr_visitor visitor_func);

#endif
