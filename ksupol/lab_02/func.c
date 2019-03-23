#include <stdio.h>
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
	c = allocate_matrix(n, n);
	if (!c)
		return NULL;
	return c;
}