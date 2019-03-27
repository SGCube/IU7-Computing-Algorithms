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
	int nx;
	int ny;
	double x;
	double y;
	double check;
	int rc;
	int am_x;
	int am_y;
	double **matrix = NULL;
	//double **result_x = NULL;
	
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
	rc = read_from_file(g, &am_x, &am_y, &matrix);
	if (rc != OK)
	{
		err_code(rc);
		fclose(g);
		return ERR;
	}
	//sort(am_x * am_y, matrix, 0);
	//sort(am_y * am_y, matrix, 1);
	printf("\n\tX\t\tY\t\tZ\n");
	print_matrix(matrix, am_x * am_y, 3);
	
	printf("Enter nx: ");
	rc = scanf("%d", &nx);
	if (rc != 1 || nx <= 0)
	{
		printf("Wrong nx!\n");
		return WR_N;
	}
	printf("Enter ny: ");
	rc = scanf("%d", &ny);
	if (rc != 1 || ny <= 0)
	{
		printf("Wrong ny!\n");
		return WR_N;
	}
	if (nx > am_x - 1)
	{
		printf("There is not enough elements in the table for this nx!\n");
		return ERR;
	}
	if (ny > am_y - 1)
	{
		printf("There is not enough elements in the table for this ny!\n");
		return ERR;
	}
	printf("Enter x: ");
	check = scanf("%lf", &x);
	if (check != 1)
	{
		printf("Wrong x!\n");
		return ERR;
	}
	printf("Enter y: ");
	check = scanf("%lf", &y);
	if (check != 1)
	{
		printf("Wrong x!\n");
		return ERR;
	}
	/*
	int up, down;
	int inter = find_interval(n, amount, matrix, x, &up, &down);
	if (inter == -1)
		printf("X is out of the table, it is too small!\n");
	else if (inter == -2)
		printf("X is out of the table, it is too big!\n");
	result_x = diff(matrix, up, down, n);
	if (!result_x)
	{
		printf("Memory allocation error!");
		return ERR;
	}
	double res = interpolate(result_x, n, x, matrix, up);
	*/
	double res = 0;
	printf("\nResult:\tz(%lf, %lf) = %lf\n", x, y, res);
	printf("True result:\yz(%lf, %lf) = %lf\n", x, y, f(x, y));
	if (matrix != NULL)
		free_matrix(matrix);
	return OK;
}