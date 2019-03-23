#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "err.h"
#include "matrix.h"
#include "function.h"

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
	double x;
	double check;
	int rc;
	int amount = 0;
	int am_koef = 0;
	double **matrix = NULL;
	double **koeff = NULL;
	double **c = NULL;
	
	setbuf(stdout, NULL);
	if (argc < 2)
	{
		printf("Not enough data!\n");
		return NOT_EN;
	}
	
	FILE *g = fopen(argv[1], "r");
	if (!g)
	{
		printf("There is no such file!\n");
		return NO_SUCH;
	}
	rc = read_from_file(g, &amount, &matrix);
	if (rc != OK)
	{
		printf("rc = %d\n", rc);
		err_code(rc);
		fclose(g);
		return ERR;
	}
	sort(amount, matrix);
	print_matrix(matrix, amount, 2);
	printf("Enter x: ");
	check = scanf("%lf", &x);
	if (check != 1)
	{
		printf("Wrong x!\n");
		return ERR;
	}
	am_koef = amount + 1;
	koeff = create_table_koeff(matrix, am_koef);
	printf("Matrix with koeff a, b, c, d:\n");
	print_matrix(koeff, 4, am_koef);
	c = create_table_c(matrix, am_koef);
	printf("Diagonal matrix:\n");
	print_matrix(c, am_koef, am_koef);
	if (!koeff)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	else
		free_matrix(koeff, amount);
	if (matrix != NULL)
		free_matrix(matrix, amount);
	return OK;
}