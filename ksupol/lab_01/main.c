#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "err.h"
#include "matrix.h"

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
	//double y;
	double check;
	int rc;
	int amount = 0;
	double **matrix = NULL;
	double **result_x = NULL;
	//double **result_y = NULL;
	
	setbuf(stdout, NULL);
	if (argc < 2)
	{
		printf("Not enough data!\n");
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
	sort(amount, matrix);
	print_matrix(matrix, amount, 2);
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
		printf("Wrong x!\n");
		return ERR;
	}
	int up, down;
	int inter = find_interval(n, amount, matrix, x, &up, &down);
	if (inter == -1)
		printf("X is out of the table, it is too small!\n");
	else if (inter == -2)
		printf("X is out of the table, it is too big!\n");
	printf("up = %d down = %d\n", up, down);
	result_x = diff(matrix, up, down, n);
	if (!result_x)
	{
		printf("Memory allocation error!");
		return ERR;
	}
	interpolate(result_x, n, x, matrix);
	if (matrix != NULL)
		free_matrix(matrix);
	fclose(f);
	return OK;
}