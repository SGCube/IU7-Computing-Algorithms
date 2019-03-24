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
	if (!koeff)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	c = create_table_c(matrix, am_koef);
	if (!c)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	printf("Diagonal matrix:\n");
	print_matrix(c, am_koef + 1, am_koef + 1);
	double *ff = NULL;
	ff = create_f(matrix, am_koef);
	if (!ff)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	double *c_koeff = NULL;
	c_koeff = find_c_koeff(c, ff, am_koef);
	if (!c_koeff)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	fill_table_koeff(matrix, koeff, c_koeff, am_koef);
	printf("Matrix with koeff a, b, c, d:\n");
	print_matrix(koeff, 4, am_koef);
	int from = 0, to = 0;
	int j = find_interval(x, &from, &to, matrix, amount);
	if (j == -1)
		printf("X is out of the table, it is too small!\n");
	else if (j == -2)
		printf("X is out of the table, it is too big!\n");
	float y = find_y(from, to, x, koeff, matrix);
	printf("y(%lf) = %lf\n real = y(%lf) = %lf\n", x, y, x, f(x));
	if (c != NULL)
		free_matrix(c, am_koef + 1);
	if (ff != NULL)
		free(ff);
	if (koeff != NULL)
		free_matrix(koeff, am_koef);
	if (matrix != NULL)
		free_matrix(matrix, amount);
	return OK;
}