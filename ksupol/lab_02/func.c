#include <stdio.h>
#include <stdlib.h>
#include "func.h"
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
	data[0][0] = 0;
	for (int i = 1; i < n; i++)
		data[0][i] = matrix[i-1][1];
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
	double *f = calloc(n + 1, sizeof(double));
	for (int i = 2; i < n - 1; i++)
	{
		double hi = matrix[i][0] - matrix[i - 1][0];
		double hi1 = matrix[i - 1][0] - matrix[i - 2][0];
		double yi = matrix[i][1];
		double yi1 = matrix[i - 1][1];
		double yi2 = matrix[i - 2][1];
		f[i] = -3 * ((yi - yi1)/hi - (yi1 - yi2)/hi1);
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
	c[n - 1][n - 1] = -2 * (matrix[n - 2][0] - matrix[n - 3][0]);
	return c;
}

double * create_koeff_c(double **matrix, int n)
{
	return NULL;
}

void fill_table_koeff(double *f, double **koeff, int n)
{
	/*
	for (int i = 0; i < n; i++)
		koeff[2][i] = f[i];
	*/
}