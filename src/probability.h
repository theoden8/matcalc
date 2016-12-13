#ifndef PROBABILITY_H_WTR3TMUP
#define PROBABILITY_H_WTR3TMUP

#define UNDEFINED -1
const PRECISION = 2000;

long double atold(char *s) {
	long double d;
	sscanf(s, "%Lf", &d);
	return d;
}

#endif
