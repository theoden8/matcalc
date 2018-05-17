#include "probability.h"

const int PRECISION = 2000;

long double atold(char *s) {
	long double d;
	sscanf(s, "%Lf", &d);
	return d;
}
