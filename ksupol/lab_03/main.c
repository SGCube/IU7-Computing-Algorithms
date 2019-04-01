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
	double *m_x = NULL;
	double *m_y = NULL;
	double **m_z = NULL;
	double **result_x = NULL;
	
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
	fclose(g);
	//sort(am_x * am_y, matrix, 0);
	//sort(am_y * am_y, matrix, 1);
	create_x_y(matrix, am_x, am_y, &m_x, &m_y, &m_z);
	printt_matrix(m_x, m_y, m_z, am_x, am_y);
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
	int up, down;
	int inter = find_interval(nx, am_x, m_x, x, &up, &down);
	if (inter == -1)
		printf("X is out of the table, it is too small!\n");
	else if (inter == -2)
		printf("X is out of the table, it is too big!\n");
	double *xx = calloc(am_y, sizeof(double));
	for (int i = 0; i < am_y; i++)
	{
		result_x = diff(m_z, m_x, up, down, nx, i);
		if (!result_x)
		{
			printf("Memory allocation error!");
			return ERR;
		}
		xx[i] = interpolate(result_x, nx, x, m_x, up);
		print_matrix(result_x, nx + 1, nx + 1);
	}
	inter = find_interval(ny, am_y, m_y, y, &up, &down);
	if (inter == -1)
		printf("Y is out of the table, it is too small!\n");
	else if (inter == -2)
		printf("Y is out of the table, it is too big!\n");
	double **result_y = differ(xx, m_y, up, down, ny);
	printf("last matrix:\n\n");
	print_matrix(result_y, ny + 1, ny + 1);
	double res = interpolate(result_y, ny, y, xx, up);
	printf("\nResult:\t\tz(%lf, %lf) = %lf\n", x, y, res);
	printf("True result:\tz(%lf, %lf) = %lf\n", x, y, f(x, y));
	if (m_x)
		free(m_x);
	if (m_y)
		free(m_y);
	if (matrix)
		free_matrix(matrix);
	if (xx)
		free(xx);
	if (result_y)
		free_matrix(result_y);
	return OK;
}