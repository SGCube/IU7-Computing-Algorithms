#include "function.h"
#include <math.h>
#define a0 1
#define a1 2
#define a2 3

double f(double x)
{
	return (a0 * x) / (a1 + a2 * x);
}

double df(double x)
{
	return a0/(a1 + a2*x) - (a0 * a2 * x)/pow(a1 + a2*x, 2);
}