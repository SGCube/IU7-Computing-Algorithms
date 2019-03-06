#include <cmath>
#include <cstdio>

#include "func.h"

double func(double x)
{
	return cos(x) - x;
}

void file_func(double a, double b, int n)
{
	if (n > 0)
	{
		FILE *f = fopen("data.txt", "w");
		if (!f)
			return;
		
		fprintf(f, "%d\n", n);
		
		double h = (b - a) / n;
		while (a <= b + h)
		{
			fprintf(f, "%lf %lf\n", a, func(a));
			a += h;
		}
		
		fclose(f);
	}
}
