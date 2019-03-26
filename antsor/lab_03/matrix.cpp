#include "matrix.h"

Matrix::Matrix()
{
	matr = nullptr;
	size_x = 0;
	size_y = 0;
}

Matrix::~Matrix()
{
	delete [] matr[0];
	delete [] matr;
}

void Matrix::read_matrix(FILE *f, int kx, int ky)
{
	matrix = new double* [kx];
	if (!matrix)
		return;
	double *data = new double[kx * ky];
	if (!data)
	{
		delete [] matrix;
		return;
	}

	for (int i = 0; i < kx; i++)
		for (int j = 0; i < ky; j++)
			if (fscanf(f, "%lf", &matrix[i][j]) != 1)
			{
				clear();
				return;
			}

	size_x = kx;
	size_y = ky;
}

void Matrix::print()
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; i < size_y; j++)
			printf("%.4lf\t", matrix[i][j]);
		printf("\n");
	}
}

void clear()
{
	delete [] matr[0];
	delete [] matr;
	matr = nullptr;
	size_x = 0;
	size_y = 0;
}
