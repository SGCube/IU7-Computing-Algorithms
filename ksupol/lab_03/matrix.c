#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#define OK 0
#define WR_ELEM -4
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

int read_matrix(double ***matrix, int am, FILE *f)
{
	double rc = 0;
	int kol = 0;
	
	for (int i = 0; i < am; i++)
	{
		for (int j = 0; j < 3; j++)
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
	else if (kol < am * 3)
		return NOT_EN;
	return OK;
}

void print_matrix(double **matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%lf\t", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printt_matrix(double *m_x, double *m_y, double **m_z, 
					int n, int m)
{
	printf("X|Y\t\t");
	for (int j = 0; j < m; j++)
		printf("(%lf)\t", m_y[j]);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("(%lf)\t", m_x[i]);
		for (int j = 0; j < m; j++)
			printf("%lf\t", m_z[i][j]);
		printf("\n");
	}
	printf("\n");
}

void free_matrix(double **matrix)
{
	free(matrix[0]);
	free(matrix);
}