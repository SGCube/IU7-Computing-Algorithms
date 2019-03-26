#include "matrix.h"

void clear_matrix(double **a)
{
	delete [] a[0];
	delete [] a;
}

double **read_matrix(FILE *f, int kx, int ky)
{
	double **marows = new double* [kx];
	if (!marows)
		return nullptr;
	double *matrix = new double[kx * ky];
	if (!matrix)
	{
		free(matrix);
		return nullptr;
	}

	double z;
	for (int i = 0; i < kx; i++)
		for (int j = 0; i < ky; j++)
			if (fscanf(f, "%lf", &matrix[i][j]) != 1)
			{
				clear_matrix(matr);
				return nullptr;
			}
	return marows;
}

void print_matrix(double **matrix, int kx, int ky)
{
	if (matrix)
		for (int i = 0; i < kx; i++)
		{
			for (int j = 0; i < ky; j++)
				printf("%.4lf\t", matrix[i][j]);
		}
}
