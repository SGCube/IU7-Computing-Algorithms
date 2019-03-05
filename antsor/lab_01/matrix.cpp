#include "matrix.h"

void clear_matrix(double **a, int n)
{
	for (int i = 0; i < n; i++)
		delete [] plist[i];
	delete [] plist;
}

double **read_matrix(std::ifstream f, int *k)
{
	double x, y;
	double **plist = nullptr;
	
	std::cin >> *k;
	if (std::cin.fail() || *k < 1)
	{
		std::cin.clear();
		std::cin.ignore(32767,'\n');
		return nullptr;
	}
	
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
		std::cin >> x >> y;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767,'\n');
			clear_matrix(plist, n);
			return nullptr;
		}
		plist[i][0] = x;
		plist[i][1] = y;
	}
	return plist;
}
