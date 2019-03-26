#include "matrix.h"

Matrix::Matrix()
{
	matr = nullptr;
	size_x = 0;
	size_y = 0;
}

Matrix::Matrix(int nx, int ny)
{
	matr = new double* [nx];
	if (!matr)
		return;
	double *data = new double[nx * ny];
	if (!data)
	{
		delete [] matr;
		return;
	}
	size_x = nx;
	size_y = ny;
}

Matrix::~Matrix()
{
	delete [] matr[0];
	delete [] matr;
}

void Matrix::read(FILE *f, int kx, int ky)
{
	matr = new double* [kx];
	if (!matr)
		return;
	double *data = new double[kx * ky];
	if (!data)
	{
		delete [] matr;
		return;
	}

	for (int i = 0; i < kx; i++)
		for (int j = 0; i < ky; j++)
			if (fscanf(f, "%lf", &matr[i][j]) != 1)
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
			printf("%.4lf\t", matr[i][j]);
		printf("\n");
	}
}

void Matrix::clear()
{
	delete [] matr[0];
	delete [] matr;
	matr = nullptr;
	size_x = 0;
	size_y = 0;
}
