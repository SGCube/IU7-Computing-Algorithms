#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <math.h>

#define OK 0
#define WR_ELEM -4
#define EMPTY 2
#define WR_AM 3
#define ERR_MALLOC 5
#define NOT_EN 6
#define NO_MAT 7

double **allocate_matrix(int n, int m)
{
	double **matrix;
	matrix = malloc(n * sizeof(double *));
	if (!matrix)
		return NULL;
	double *data = calloc(n * m, sizeof(double));
	if (!data)
	{
		free(matrix);
		return NULL;
	}
	for (int i = 0; i < n; i++)
		matrix[i] = data + i * m;
	return matrix;
}

int read_matrix(double ***matrix, int n, FILE *f)
{
	double rc = 0;
	int kol = 0;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rc = fscanf(f, "%lf", &(*matrix)[i][j]);
			if (rc != 1 && rc != EOF)
				return WR_ELEM;
			else if (rc == 1)
				kol++;
		}
	}
	if (kol == 0)
		return NO_MAT;
	else if (kol < n * 2)
		return NOT_EN;
	return OK;
}

void print_matrix(double **matrix, int n, int m)
{
	printf("\nMatrix:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%lf ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

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

void free_matrix(double **matrix)
{
	free(matrix[0]);
	free(matrix);
}

void sort(int n, double **matrix)
{
	double *tmp = NULL;
	setbuf(stdout, NULL);
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

int find_interval(int n, int a, double **matrix, double x, 
		int *up, int *down)
{
	if (x < matrix[0][0])
	{
		*up = 0;
		*down = n;
		return -1;
	}
	if (x > matrix[a-1][0])
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
		if (x >= matrix[i+1][0])
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