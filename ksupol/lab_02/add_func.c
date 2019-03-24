#include <stdio.h>
#include <math.h>
#include "function.h"

#define OK 0
#define ERR -1

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Not enough data!\n");
		return ERR;
	}
	setbuf(stdout, NULL);
	int amount;
	int rc;
	double from;
	double to;
	double step;
	printf("Enter point 'from': ");
	rc = scanf("%lf", &from);
	if (rc != 1)
	{
		printf("Wrong point 'from'!\n");
		return ERR;
	}
	printf("\nEnter point 'to': ");
	rc = scanf("%lf", &to);
	if (rc != 1)
	{
		printf("Wrong point 'to'!\n");
		return ERR;
	}
	printf("\nEnter step: ");
	rc = scanf("%lf", &step);
	if (rc != 1)
	{
		printf("Wrong step!\n");
		return ERR;
	}
	FILE *g = fopen(argv[1], "w");
	if (!g)
	{
		printf("Couldn't open file!\n");
		return ERR;
	}
	amount = (to - from) / step + 1;
	fprintf(g, "%d\n", amount);
	for (double i = from; i <= to; i += step)
		fprintf(g, "%lf\t%f\n", i, f(i));
	fclose(g);
	return 0;
}