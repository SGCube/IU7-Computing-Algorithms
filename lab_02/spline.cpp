#include <cmath>
#include <stdlib.h>

#include "spline.h"
#include "matrix.h"

int cmp_point_x(const void *p1, const void *p2)
{
    double *pa = (double *)p1;
    double *pb = (double *)p2;
    return pa[0] - pb[0];
}

double *sle(double **matr, int n)
{
	// matr[n + 3][n + 3], i = 1, n + 1; j = 1, n + 2
	
	double *ksi = (double *) calloc(n + 2, sizeof(double));
	if (!ksi)
		return NULL;
	double *eta = (double *) calloc(n + 2, sizeof(double));
	if (!eta)
	{
		free(ksi);
		return NULL;
	}
	double *u = (double *) calloc(n + 2, sizeof(double));
	if (!u)
	{
		free(ksi);
		free(eta);
		return NULL;
	}
	
	// A(i) - matr[i][i - 1], B(i) - matr[i][i], D(i) - matr[i][i + 1]
	// F(i) - matr[i][0]
	
	/*	ksi[1] = ???;
		eta[1] = ???;
		ksi[2] = 0;
		eta[2] = 0;
		u[1] = 0;
		u[n + 1] = 0;	*/
	
	for (int i = 2; i <= n; i++)
	{
		ksi[i + 1] = matr[i][i + 1] / (matr[i][i] - matr[i][i - 1] * ksi[i - 1]);
		eta[i + 1] = (matr[i][i - 1] * eta[i - 1] + matr[i][0]) / (matr[i][i]);
	}
	
	for (int i = n; i > 1; i--)
		u[i] = ksi[i + 1] * u[i + 1] + eta[i + 1];
	
	free(eta);
	free(ksi);
	return u;
}

double **spline(double **plist, int n)
{
	// i = 1, n; 0, n + 1 - extra
	double **koefs = calloc_matrix(4, n + 2);
	if (!koefs)
		return NULL;
	
	// i = 1, n + 1; 0, n + 2 - extra
	double **c_sle = calloc_matrix(n + 3, n + 3);
	if (!c_sle)
	{
		free_matrix(koefs, 4);
		return NULL;
	}
	
	double hi = plist[2][0] - plist[1][0];
	double hi_1 = plist[1][0] - plist[0][0];
	double yi = plist[2][1] - plist[1][1];
	double yi_1 = plist[1][1] - plist[0][1];
	
	for (int i = 2; i <= n; i++)
	{
		hi = plist[i][0] - plist[i - 1][0];
		yi = plist[i][1] - plist[i - 1][1];
		
		c_sle[i][i - 1] = hi_1;							// A(i)
		c_sle[i][i] = -2 * (hi + hi_1);					// B(i)
		c_sle[i][i + 1] = hi;							// D(i)
		c_sle[i][0] = -3 * (yi / hi - yi_1 / hi_1);		// F(i)
		
		hi_1 = hi;
		yi_1 = yi;
	}
	
	// c(i)
	free(koefs[2]);
	koefs[2] = sle(c_sle, n);
	free_matrix(c_sle, n + 3);
	if (!koefs[2])
	{
		free_matrix(koefs, 4);
		return NULL;
	}
	
	for (int i = n; i > 0; i--)
	{
		hi = plist[i][0] - plist[i - 1][0];
		yi = plist[i][1] - plist[i - 1][1];
		
		// d(i)
		koefs[3][i] = (koefs[2][i + 1] - koefs[2][i]) / (3 * hi);
		// b(i)
		koefs[1][i] = yi / hi - hi * (koefs[2][i + 1] + 2 * koefs[2][i]) / 3;
		// a(i)
		koefs[0][i] = plist[i - 1][1];
	}
	
	return koefs;
}

double solve(double **plist, double x, int n)
{
    qsort(plist, n + 1, sizeof(double *), cmp_point_x);
	double y;
	if (n > 2)
	{
	
		double **splines = spline(plist, n);
		if (!splines)
			return -1;
		
		int i = 1;
		while (i <= n && x > plist[i][0])
			i++;
		
		double h = x - plist[i - 1][0];
		y = splines[0][i];
		double hh = h;
		
		for (int j = 1; j < 4; j++)
		{
			y += splines[j][i] * hh;
			hh *= h;
		}
		
		//print_matrix(splines, 4, n + 2);
		free_matrix(splines, 4);
	}
	else
	{
		double xi = x - plist[0][0];
		double yi = plist[1][1] - plist[0][1];
		double hi = plist[1][0] - plist[0][0];
		y = plist[0][1] + yi / hi * xi;
	}
	
    return y;
}
