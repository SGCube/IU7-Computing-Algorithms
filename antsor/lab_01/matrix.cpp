#include "matrix.h"

void clear_matrix(double **a, int n)
{
	for (int i = 0; i < n; i++)
		delete [] a[i];
	delete [] a;
}

double **read_matrix(ifstream &f, int *k)
{
	double x, y;
	double **plist = nullptr;
	
	f >> *k;
	if (f.fail() || *k < 1)
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
		f >> x >> y;
		if (f.fail())
		{
			clear_matrix(plist, *k);
			return nullptr;
		}
		plist[i][0] = x;
		plist[i][1] = y;
	}
	return plist;
}
