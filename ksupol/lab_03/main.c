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
	double *m_x = NULL; //матрица x
	double *m_y = NULL; //матрица y
	double **m_z = NULL; //матрица z
	double **result_x = NULL; //матрица разделенных разн при интерпол по x
	
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
	int up, down; //вернхняя и нижняя граница матрицы разделенных разностей
	int inter = find_interval(nx, am_x, m_x, x, &up, &down);
	if (inter == -1)
		printf("X is out of the table, it is too small!\n");
	else if (inter == -2)
		printf("X is out of the table, it is too big!\n");
	
	double *z = calloc(am_y, sizeof(double));
	for (int i = 0; i < am_y; i++)
	{
		result_x = diff(m_z, m_x, up, down, nx, i);
		if (!result_x)
		{
			printf("Memory allocation error!");
			return ERR;
		}
		z[i] = interpolate(result_x, nx, x, m_x, up);
	}
	inter = find_interval(ny, am_y, m_y, y, &up, &down);
	if (inter == -1)
		printf("Y is out of the table, it is too small!\n");
	else if (inter == -2)
		printf("Y is out of the table, it is too big!\n");
	double **result_y = differ(z, m_y, up, down, ny);
	double res = interpolate(result_y, ny, y, m_y, up);
	printf("\nResult:\t\tz(%lf, %lf) = %lf\n", x, y, res);
	printf("True result:\tz(%lf, %lf) = %lf\n", x, y, f(x, y));
	if (m_x)
		free(m_x);
	if (m_y)
		free(m_y);
	if (matrix)
		free_matrix(matrix);
	if (z)
		free(z);
	if (result_y)
		free_matrix(result_y);
	return OK;
}