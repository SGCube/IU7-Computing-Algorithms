#include <stdio.h>
#include <math.h>

double f(double x)
{
	return sin(x + 90);
}

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	int am;
	double from;
	double to;
	double step;
	printf("Enter from and to and step: ");
	scanf("%lf %lf %lf", &from, &to, &step);
	FILE *g = fopen(argv[1], "w");
	if (!g)
		return -1;
	am = (to - from) / step + 1;
	fprintf(g, "%d\n", am);
	for (double i = from; i <= to; i += step)
		fprintf(g, "%lf\t%f\n", i, f(i));
	fclose(g);
	return 0;
}