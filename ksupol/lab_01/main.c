#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "err.h"

#define WR_AM 3
#define EMPTY 2
#define ERR 1
#define OK 0
#define WR_AC -1
#define WR_N -2
#define ERR_MALLOC -3
#define WR_ELEM -4
#define WR_CH -5
#define NOT_EN 6
#define NO_SUCH -7

int main(int argc, char **argv)
{
	int n;
	double x;
	double check;
	int rc;
	int amount = 0;
	double **matrix = NULL;
	
	setbuf(stdout, NULL);
	if (argc < 2)
	{
		printf("Not enought data!\n");
		return NOT_EN;
	}
	
	FILE *f = fopen(argv[1], "r");
	if (!f)
	{
		printf("There is no such file!\n");
		return NO_SUCH;
	}
	rc = read_from_file(f, &amount, &matrix);
	if (rc != OK)
	{
		printf("rc = %d\n", rc);
		err_code(rc);
		fclose(f);
		return ERR;
	}
	printf("Enter n: ");
	rc = scanf("%d", &n);
	if (rc != 1 || n <= 0)
	{
		printf("Wrong n!\n");
		return WR_N;
	}
	if (n > amount - 1)
	{
		printf("There is not enough elements in the table!\n");
		return ERR;
	}
	printf("Enter x: ");
	check = scanf("%lf", &x);
	if (check != 1)
	{
		printf("Wrong x!");
		return ERR;
	}
	if (matrix != NULL)
		free_matrix(matrix);
	fclose(f);

	return OK;
}