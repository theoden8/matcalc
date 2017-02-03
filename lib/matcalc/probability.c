#include "probability.h"

const PRECISION = 2000;

long double atold(char *s) {
	long double d;
	sscanf(s, "%Lf", &d);
	return d;
}
