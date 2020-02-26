#include <cstdio>
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
		int i = 0;
		while (i < n)
		{
			fprintf(f, "%lf %lf\n", a, func(a));
			a += h;
			i++;
		}
		
		fclose(f);
	}
}
