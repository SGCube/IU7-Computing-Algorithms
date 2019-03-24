#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "spline.h"
#include "matrix.h"

#define WR_AM 3
#define EMPTY 2
#define ERR 1
#define OK 0
#define ERR_MALLOC -3
#define WR_ELEM -4
#define NOT_EN 6
#define NO_SUCH -7

int read_from_file(FILE *f, int *amount, double ***matrix)
{
	int rc;
	
	rc = fscanf(f, "%d", amount);
	if (rc == EOF)
		return EMPTY;
	if (rc != 1 || *amount <= 0)
		return WR_AM;
	*matrix = allocate_matrix(*amount, 2);
	if (!*matrix)
		return ERR_MALLOC;
	rc = read_matrix(matrix, *amount, f);
	if (rc != OK)
		return rc;
	return OK;
}

void sort(int n, double **matrix)
{
	double *tmp = NULL;
	for (int i = 1; i < n; i++)
	{
        for (int j = 1; j < n; j++)
		{
            if (matrix[j][0] < matrix[j-1][0])
			{
                tmp = matrix[j];
                matrix[j] = matrix[j-1];
                matrix[j-1] = tmp;
            }
        }
	}
}

double **create_table_koeff(double **matrix, int n)
{
	double **data = NULL;
	data = allocate_matrix(4, n);
	if (!data)
		return NULL;
	for (int i = 1; i < n; i++)
		data[0][i] = matrix[i - 1][1];
	return data;
}

double **create_table_c(double **matrix, int n)
{
	double **c = NULL;
	c = allocate_matrix(n + 1, n + 1);
	if (!c)
	{
		free_matrix(c, n);
		return NULL;
	}
	for (int i = 0; i < n; i++)
	{
		c[0][i] = 0;
		c[n-1][i] = 0;
	}
	int m = 0;
	int j = 0;
	for (int i = 1; i < n - 1; i++)
	{
		if (i == 1)
		{
			c[i][m] = 0;
			c[i][m + 1] = 0;
		}
		else
		{
			c[i][m] = matrix[j + 1][0] - matrix[j][0];
			c[i][m + 1] = -2 * (matrix[j + 1][0] - matrix[j][0] +
								matrix[j + 2][0] - matrix[j + 1][0]);
			j++;
		}
		c[i][m + 2] = matrix[i][0] - matrix[i - 1][0];
		m++;
		
	}
	c[n - 1][n - 2] = matrix[n - 2][0] - matrix[n - 3][0];
	c[n - 1][n - 1] = -2 * (matrix[n - 2][0] - matrix[n - 3][0] +
							matrix[n - 1][0] - matrix[n - 2][0]);
	
	return c;
}

double *create_f(double **matrix, int n)
{
	double *f = calloc(n + 1, sizeof(double));
	if (!f)
		return NULL;
	for (int i = 2; i < n - 1; i++)
	{
		double hi = matrix[i][0] - matrix[i - 1][0];
		double hi1 = matrix[i - 1][0] - matrix[i - 2][0];
		double yi = matrix[i][1];
		double yi1 = matrix[i - 1][1];
		double yi2 = matrix[i - 2][1];
		f[i] = -3 * ((yi - yi1)/hi - (yi1 - yi2)/hi1);
	}
	return f;
}

double *find_c_koeff(double **c, double *f, int n)
{
	double *c_koeff = calloc(n + 1, sizeof(double));
	if (!c_koeff)
		return NULL;
	double *kk = calloc(n + 1, sizeof(double));
	if (!kk)
		return NULL;
	double *nn = calloc(n + 1, sizeof(double));
	if (!nn)
		return NULL;
	int m = 1;
	for (int i = 2; i < n + 1; i++)
	{
		double ai = c[i][m];
		double bi = c[i][m + 1];
		double di = c[i][m + 2];
		kk[i + 1] = di/(bi - ai*kk[i]);
		nn[i + 1] = (ai*nn[i] + f[i])/(bi - ai*kk[i]);
		m++;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		c_koeff[i] = kk[i + 1] * c_koeff[i + 1] + nn[i + 1];
	}
	return c_koeff;
}

void fill_table_koeff(double **m, double **koeff, double *c, int n)
{
	for (int i = 0; i < n; i++)
		koeff[2][i] = c[i];
	for (int i = 1; i < n - 1; i++)
	{
		double yi = m[i][1];
		double yi1 = m[i - 1][1];
		double hi = m[i][0] - m[i - 1][0];
		koeff[1][i] = (yi - yi1)/hi - 1/3*hi*(c[i+1] + 2*c[i]);
		koeff[3][i] = (c[i + 1] - c[i])/ 3*hi;
	}
}

int find_interval(double x, int *from, int *to, double **matr, int n)
{
	if (x < matr[0][0])
	{
		*from = 0;
		*to = 1;
		return -1;
	}
	if (x > matr[n - 1][0])
	{
		*from = n - 2;
		*to = n - 1;
		return -2;
	}
	if (x == matr[n - 1][0])
	{
		*from = n - 2;
		*to = n - 1;
		return 0;
	}
	int ii = -1;
	for (int i = 0; i < n; i++)
	{
		if (x >= matr[i][0] && x < matr[n -1][0])
			ii++;
	}
	*from = ii;
	*to = ii + 1;
	return 0;
}

float find_y(int from, int to, double x, double **k, double **matr)
{
	double xi1 = matr[from][0];
	double y = k[0][to] + k[1][to]*(x - xi1) +
			k[2][to]*pow((x - xi1), 2) + k[3][to]*pow((x - xi1), 3);
	return y;
}