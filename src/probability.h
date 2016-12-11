#ifndef PROBABILITY_H_WTR3TMUP
#define PROBABILITY_H_WTR3TMUP

long double get_double(int n, char *argv[]) {
	long double d;
	sscanf(argv[n], "%Lf", &d);
	return d;
}

#endif
