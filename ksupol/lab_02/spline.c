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
	data = allocate_matrix(4, n + 2);
	if (!data)
		return NULL;
	for (int i = 0; i > 0; i--)
		data[0][i] = matrix[i - 1][1];
	return data;
}

double **create_table_c(double **m, int n, double **f)
{
	double **c = NULL;
	c = allocate_matrix(n + 3, n + 3);
	if (!c)
	{
		free_matrix(c, n + 3);
		return NULL;
	}
	*f = calloc(n + 3, sizeof(double));
	if (!*f)
		return NULL;
	double hi = m[2][0] - m[1][0];
	double hi1 = m[1][0] - m[0][0];
	double yi = m[2][1] - m[1][1];
	double yi1 = m[1][1] - m[0][1];
	for (int i = 2; i <= n; i++)
	{
		hi = m[i][0] - m[i - 1][0];
		yi = m[i][1] - m[i - 1][1];

		c[i][i - 1] = hi1;
		c[i][i] = -2 * (hi + hi1);
		c[i][i + 1] = hi;
		(*f)[i] = -3 * (yi / hi - yi1 / hi1);
		
		hi1 = hi;
		yi1 = yi;
	}
	return c;
}

double *find_c_koeff(double **c, double *f, int n, double **matr)
{
	double *c_koeff = calloc(n + 2, sizeof(double));
	if (!c_koeff)
		return NULL;
	double *kk = calloc(n + 2, sizeof(double));
	if (!kk)
	{
		free(c_koeff);
		return NULL;
	}		
	double *nn = calloc(n + 2, sizeof(double));
	if (!nn)
	{
		free(c_koeff);
		free(kk);
		return NULL;
	}
	for (int i = 2; i <= n; i++)
	{
		double ai = c[i][i - 1];
		double bi = c[i][i];
		double di = c[i][i + 1];
		
		kk[i + 1] = di/(bi - ai*kk[i]);
		nn[i + 1] = (ai*nn[i] + f[i])/(bi - ai*kk[i]);
	}
	for (int i = n; i > 1; i--)
		c_koeff[i] = kk[i + 1] * c_koeff[i + 1] + nn[i + 1];
	free(kk);
	free(nn);
	return c_koeff;
}

void fill_table_koeff(double **m, double **koeff, double *c, int n)
{
	for (int i = n; i > 0; i--)
		koeff[2][i] = c[i];
	for (int i = n; i > 0; i--)
	{
		double hi = m[i][0] - m[i - 1][0];
		double yi = m[i][1];
		double yi1 = m[i - 1][1];
		
		koeff[1][i] = (yi - yi1)/hi - hi*(koeff[2][i+1] + 2*koeff[2][i])/3;
		koeff[3][i] = (koeff[2][i+1] - koeff[2][i])/(3 * hi);
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