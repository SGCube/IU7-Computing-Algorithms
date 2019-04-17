#include <cstdio>
#include <cmath>
#include "func.h"

void file_func(double a, double b, double h, double (*func)(double))
{
	if (h != 0)
	{
		FILE *f = fopen("data.txt", "w");
		if (!f)
			return;
		
		int n = (b - a) / h + 1;
		fprintf(f, "%d\n", n);
		
		while (a <= b)
		{
			fprintf(f, "%lf %lf %d\n", a, func(a), 1);
			a += h;
		}
		
		fclose(f);
	}
}

double f(double x, double k)
{
	return pow(x, k);
}
