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