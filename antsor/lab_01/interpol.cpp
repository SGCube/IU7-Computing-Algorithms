#include <cmath>
#include <stdlib.h>

#include "interpol.h"

int cmp_point_x(void *p1, void *p2)
{
    double *pa = (double *)p1;
    double *pb = (double *)p2;
    return pa[0] - pb[0];
}

double **surround(double plist[][2], double x, int n, int k)
{
    double **parr = NULL;
    int i = 0;
    while (i < k && x < plist[i][0])
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
    for (int i = left; i <= right; i++)
    {
        parr[i] = new double [2];
        parr[i][0] = parr[i][0];
        parr[i][1] = parr[i][1];
    }
    return parr;
}

double newton(double x, int n, double *parr)
{
    double **dy = new double* [n];
    for (int i = 0; i < n + 1; i++)
    {
        dy[i] = new double [n + 1];
        dy[i][0] = parr[i][1];
    }

    for (int i = 1; i < n + 1; i++)
        for (int j = 0; j < n + 1 - i; j++)
            dy[j][i] = (dy[j][i - 1] - dy[j + 1][i - 1]) /
                    (parr[j][0] - parr[j + i][0]);

    double res = dy[0][0];
    double xpr = 1;
    for (int i = 1; i < n + 1; i++)
    {
        xpr *= x - parr[i - 1][0];
        res += dy[i][0] * xpr;
    }

    delete [] dy;

    return res;
}

double solve(double plist[][2], double x, int n, int k)
{
    qsort(plist, k, sizeof(double *), cmp_point_x);
    parr = surround(plist, x, n, k);
    if (parr)
        return newton(x, n, parr);
    return -1;
}
