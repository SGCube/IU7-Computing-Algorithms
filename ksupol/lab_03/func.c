#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "matrix.h"
#include "function.h"

#define OK 0
#define WR_ELEM -4
#define EMPTY 2
#define WR_AM 3
#define ERR_MALLOC 5
#define NOT_EN 6
#define NO_MAT 7

int read_from_file(FILE *f, int *am_x, int *am_y, double ***matrix)
{
	int rc;
	
	rc = fscanf(f, "%d", am_x);
	if (rc == EOF)
		return EMPTY;
	if (rc != 1 || *am_x <= 0)
		return WR_AM;
	rc = fscanf(f, "%d", am_y);
	if (rc == EOF)
		return NOT_EN;
	if (rc != 1 || *am_y <= 0)
		return WR_AM;
	*matrix = allocate_matrix((*am_x) * (*am_y), 3);
	if (!*matrix)
		return ERR_MALLOC;
	rc = read_matrix(matrix, (*am_x) * (*am_y), f);
	return OK;
}

int create_x_y(double **matrix, int am_x, int am_y, double **m_x,
				double **m_y, double ***m_z)
{
	*m_x = calloc(am_x, sizeof(double));
	if (!m_x)
		return ERR_MALLOC;
	*m_y = calloc(am_y, sizeof(double));
	if (!m_y)
		return ERR_MALLOC;
	*m_z = allocate_matrix(am_x, am_y);
	if (!*m_z)
		return ERR_MALLOC;
	for (int i = 0; i < am_y; i++)
		(*m_y)[i] = matrix[i][1];
	for (int i = 0; i < am_x; i++)
		(*m_x)[i] = matrix[i * am_y][0];
	int k = 0;
	for (int i = 0; i < am_x; i++)
	{
		for (int j = 0; j < am_y; j++)
			(*m_z)[i][j] = matrix[k++][2];
	}
	return OK;
}

void sort(int n, double **matrix, int k)
{
	double *tmp = NULL;
	for (int i = 1; i < n; i++)
	{
        for (int j = 1; j < n; j++)
		{
            if (matrix[j][k] < matrix[j-1][k])
			{
                tmp = matrix[j];
                matrix[j] = matrix[j-1];
                matrix[j-1] = tmp;
            }
        }
	}
}

int find_interval(int n, int a, double *matrix, double x, 
		int *up, int *down)
{
	if (x < matrix[0])
	{
		printf("x = %lf, m = %lf\n", x, matrix[0]);
		*up = 0;
		*down = n;
		return -1;
	}
	if (x > matrix[a-1])
	{
		*up = a - n - 1;
		*down = a - 1;
		return -2;
	}
	if (a - 1 == n)
	{
		*up = 0;
		*down = a - 1;
		return OK;
	}
	int ii = 0;
	for (int i = 0; i < a - 1; i++)
	{
		if (x >= matrix[i+1])
			ii++;
		else
			break;
	}
	//если кол-во узлов четное
	if ((n + 1) % 2 == 0)
	{
		if (ii - (n + 1)/2 >= 0 && ii + (n + 1)/2 <= a - 1)
		{
			*up = ii - (n + 1)/2 + 1;
			*down = ii + (n + 1)/2;
		}
		if (ii - (n + 1)/2 < 0)
		{
			*up = 0;
			*down = n;
		}
		if (ii + (n + 1)/2 > a)
		{
			*up = ii - n;
			*down = a - 1;
		}
	}
	//если кол-во узлов нечетное
	else
	{
		if (ii - n / 2 >= 0 && ii + n / 2 <= a - 1)
		{
			*up = ii - n / 2;
			*down = ii + n / 2;
		}
		if (ii - n / 2 < 0)
		{
			*up = 0;
			*down = n;
		}
		if (ii + n/2 > a - 1)
		{
			*up = ii - n;
			*down = a - 1;
		}
	}
	return OK;
}

double **diff(double **m_z, double *m_x, int up, int down, int n, 
				int p)
{
	double **result;
	result = allocate_matrix(n + 1, n + 1);
	if (!*result)
		return NULL;
	int k = 0;
	for (int i = up; i <= down; i++)
		result[k++][0] = m_z[i][p];

	for (int i = 1; i < n + 1; i++)
	{
        for (int j = 0; j < n + 1 - i; j++)
		{
            result[j][i] = (result[j + 1][i - 1] - result[j][i - 1]) /
                    (m_x[j + up + i] - m_x[j + up]);
		}
	}
	return result;
}


double **differ(double *m_z, double *m_x, int up, int down, int n)
{
	double **result;
	result = allocate_matrix(n + 1, n + 1);
	if (!*result)
		return NULL;
	int k = 0;
	for (int i = up; i <= down; i++)
		result[k++][0] = m_z[i];
	
	for (int i = 1; i < n + 1; i++)
	{
        for (int j = 0; j < n + 1 - i; j++)
		{
			result[j][i] = (result[j + 1][i - 1] - result[j][i - 1]) /
                    (m_x[j + up + i] - m_x[j + up]);
		}
	}
	return result;
}

double interpolate(double **result, int n, double x, double *m_x,
				int up)
{
	double res = result[0][0];
	int p = 0;
	for (int i = 1; i < n + 1; i++)
	{
		double k = x * result[0][i];
		for (int j = 0; j < p; j++)
			k *= x - m_x[up + i + j];
		p++;
		res += k;
	}
	printf("res = %lf\n", res);
	return res;
}