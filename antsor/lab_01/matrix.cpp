#include "matrix.h"

void clear_matrix(double **a, int n)
{
	for (int i = 0; i < n; i++)
		delete [] a[i];
	//delete [] a;
}

double **read_matrix(FILE *f, int *k)
{
	double x, y;
	double **plist = nullptr;

	if (fscanf(f, "%d", k) != 1 || *k < 1)
		return nullptr;
	
	plist = new double* [*k];
	if (!plist)
		return nullptr;
	for (int i = 0; i < *k; i++)
	{
		plist[i] = new double [2];
		if (!plist[i])
		{
			clear_matrix(plist, i);
			return nullptr;
		}
	}
	
	for (int i = 0; i < *k; i++)
	{
		if (fscanf(f, "%lf%lf", &x, &y) != 2)
		{
			clear_matrix(plist, *k);
			return nullptr;
		}
		plist[i][0] = x;
		plist[i][1] = y;
	}
	return plist;
}

void print_matrix(double **plist, int k)
{
	if (plist)
		for (int i = 0; i < k; i++)
			printf("%.3lf\t|%.3lf\n", plist[i][0], plist[i][1]);
}
