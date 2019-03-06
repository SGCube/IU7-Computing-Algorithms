#include <cmath>
#include <cstdio>

#include "func.h"

double func(double x)
{
	return x * x + 2;
}

void file_func(double a, double b, int n)
{
	if (n > 0)
	{
		FILE *f = fopen("data.txt", "w");
		if (!f)
			return;
		
		fprintf("%d\n", n);
		
		double h = (b - a) / n;
		while (a <= b + h)
		{
			fprintf("%lf %lf\n", a, func(a));
			a += h;
		}
		
		fclose(f);
	}
}
