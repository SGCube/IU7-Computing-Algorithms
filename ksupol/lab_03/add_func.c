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
	int am;
	int rc;
	double from_x;
	double to_x;
	double from_y;
	double to_y;
	double step_x;
	double step_y;
	printf("Enter point x 'from': ");
	rc = scanf("%lf", &from_x);
	if (rc != 1)
	{
		printf("Wrong point x 'from'!\n");
		return ERR;
	}
	printf("\nEnter point x 'to': ");
	rc = scanf("%lf", &to_x);
	if (rc != 1)
	{
		printf("Wrong point x 'to'!\n");
		return ERR;
	}
	if (from_x > to_x)
	{
		printf("Point x 'from' is bigger than point 'to'!\n");
		return ERR;
	}
	printf("\nEnter x step: ");
	rc = scanf("%lf", &step_x);
	if (rc != 1)
	{
		printf("Wrong x step!\n");
		return ERR;
	}
	
	
	printf("Enter point y 'from': ");
	rc = scanf("%lf", &from_y);
	if (rc != 1)
	{
		printf("Wrong point y 'from'!\n");
		return ERR;
	}
	printf("\nEnter point y 'to': ");
	rc = scanf("%lf", &to_y);
	if (rc != 1)
	{
		printf("Wrong point y 'to'!\n");
		return ERR;
	}
	if (from > to_y)
	{
		printf("Point y 'from' is bigger than point 'to'!\n");
		return ERR;
	}
	printf("\nEnter y step: ");
	rc = scanf("%lf", &step_y);
	if (rc != 1)
	{
		printf("Wrong y step!\n");
		return ERR;
	}
	/*
	FILE *g = fopen(argv[1], "w");
	if (!g)
	{
		printf("Couldn't open file!\n");
		return ERR;
	}
	am = (to - from) / step + 1;
	fprintf(g, "%d\n", am);
	double k = from_x;
	for (int i = 0; i < am; i++)
	{
		fprintf(g, "%lf\t%f\n", k, f(k));
		k += step;
	}
	fclose(g);
	*/
	return 0;
}