#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "interpol.h"

int cmp_double(const void *p1, const void *p2)
{
    double *pa = (double *)p1;
    double *pb = (double *)p2;
    return *pa - *pb;
}

void clear_matrix(double **a, int n)
{
	for (int i = 0; i < n; i++)
		delete [] a[i];
	//delete [] a;
}

double **surround(double *xarr, double *yarr, double x, int n, int k)
{
    double **parr = NULL;
    int i = 0;
    while (i < k && x > xarr[i])
        i++;
    int left = fmax(0, i - (n + 1)/ 2);
    int right = fmin(i + (n + 1)/ 2, k - 1);
    int d = right - left;
    if (d < n + 1)
    {
        if (left == 0)
            right = n;
        else
            left = k - n;
    }

    parr = new double* [n + 1];
    for (int i = left, j = 0; i <= right; i++, j++)
    {
        parr[j] = new double [2];
        parr[j][0] = xarr[i];
        parr[j][1] = yarr[i];
    }
    return parr;
}

double newton(double x, int n, double **parr)
{
    double **dy = new double* [n];
    for (int i = 0; i < n + 1; i++)
    {
        dy[i] = new double [n + 1];
        dy[i][0] = parr[i][1];
    }

    for (int i = 1; i < n + 1; i++)
        for (int j = 0; j < n + 1 - i; j++)
		{
            dy[j][i] = (dy[j][i - 1] - dy[j + 1][i - 1]) /
                    (parr[j][0] - parr[j + i][0]);
		}

    double res = dy[0][0];
    double xpr = 1;
    for (int i = 1; i < n + 1; i++)
    {
        xpr *= x - parr[i - 1][0];
        res += dy[0][i] * xpr;
    }
	
    clear_matrix(dy, n);
	clear_matrix(parr, n);

    return res;
}

double solve(double *xarr, double *yarr, double x, int n, int k)
{
    double **parr = surround(xarr, yarr, x, n, k);
    if (parr)
        return newton(x, n, parr);
    return -1;
}
