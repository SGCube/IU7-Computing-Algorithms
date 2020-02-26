#include <cstdlib>
#include "matrix.h"

void clear_matrix(double **a, int n)
{
	for (int i = 0; i < n; i++)
		delete [] a[i];
	//delete [] a;
}

void free_matrix(double **a, int n)
{
	for (int i = 0; i < n; i++)
		if (a[i])
			free(a[i]);
	free(a);
}

double **read_matrix(FILE *f, int *k)
{
	double x, y, p;
	double **plist = nullptr;

	if (fscanf(f, "%d", k) != 1 || *k < 1)
		return nullptr;
	
	plist = new double* [*k];
	if (!plist)
		return nullptr;
	for (int i = 0; i < *k; i++)
	{
		plist[i] = new double [3];
		if (!plist[i])
		{
			clear_matrix(plist, i);
			return nullptr;
		}
	}
	
	for (int i = 0; i < *k; i++)
	{
		if (fscanf(f, "%lf%lf%lf", &x, &y, &p) != 3)
		{
			clear_matrix(plist, *k);
			return nullptr;
		}
		plist[i][0] = x;
		plist[i][1] = y;
		plist[i][2] = p;
	}
	return plist;
}

void print_matrix(double **plist, int n, int m)
{
	if (plist)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				printf("%.3lf\t", plist[i][j]);
			printf("\n");
		}
}

double **calloc_matrix(int n, int m)
{
	double **matr = (double **) calloc(n, sizeof(double *));
	if (!matr)
		return NULL;
	for (int i = 0; i < n; i++)
	{
		matr[i] = (double *) calloc(m, sizeof(double));
		if (!matr[i])
		{
			free_matrix(matr, i);
			return NULL;
		}
	}
	return matr;
}
