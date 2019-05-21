#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"
#include "matrix.h"
#include "function.h"

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
	*matrix = allocate_matrix(*amount, 8);
	if (!*matrix)
		return ERR_MALLOC;
	rc = read_matrix(matrix, *amount, f);
	if (rc != OK)
		return rc;
	return OK;
}

void real(int amount, double **matrix)
{
	for (int i = 0; i < amount; i++)
		matrix[i][7] = df(matrix[i][0]);
}
void one_side(int amount, double **matrix)
{
	for (int i = 0; i < amount - 1; i++)
		matrix[i][2] = (matrix[i+1][1] - matrix[i][1])/(matrix[i+1][0] - matrix[i][0]);
	matrix[amount - 1][2] = 999999999;
}

void increased_accuracy(int am, double **matrix)
{
	for (int i = 1; i < am - 1; i++)
		matrix[i][3] = 999999999;
	matrix[0][3] = (-3*matrix[0][1] + 4*matrix[1][1] - matrix[2][1])/(matrix[2][0]-matrix[0][0]);
	matrix[am-1][3] = (3*matrix[am-1][1] - 4*matrix[am-2][1] + matrix[am-3][1])/(matrix[am-1][0]-matrix[am-3][0]);
}

void central(int am, double **matrix)
{
	matrix[0][4] = 999999999;
	for (int i = 1; i < am - 1; i++)
		matrix[i][4] = (matrix[i+1][1]-matrix[i-1][1])/(matrix[i+1][0]-matrix[i-1][0]);
	matrix[am - 1][4] = 999999999;
}

void runge(int am, double **matrix)
{
	double h = matrix[1][0] - matrix[0][0];
	double h2 = h * 2;
	int p = 1;
	double *vector1 = calloc(am, sizeof(double));
	double *vector2 = calloc(am, sizeof(double));
	
	for (int i = 0; i < am - 2; i++)
	{
		vector1[i] = (matrix[i+1][1] - matrix[i][1]) / h;
		vector2[i] = (matrix[i+2][1] - matrix[i][1]) / h2;
		matrix[i][5] = vector1[i] + (vector1[i] - vector2[i]) / (pow(2,p) - 1);
	}

	for (int i = am - 2; i < am; i++)
	{
		vector1[i] = (matrix[i][1] - matrix[i-1][1]) / h;
		vector2[i] = (matrix[i][1] - matrix[i-2][1]) / h2;
		matrix[i][5] = vector1[i] + (vector1[i] - vector2[i]) / (pow(2,p) - 1);
	}
	free(vector1);
	free(vector2);
}