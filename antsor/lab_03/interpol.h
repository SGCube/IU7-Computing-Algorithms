#ifndef INTERPOL_H
#define INTERPOL_H

int cmp_point_x(const void *p1, const void *p2);

void clear_matrix(double **a, int n);

double **surround(double *xarr, double *yarr, double x, int n, int k);

double newton(double x, int n, double **parr);

double solve(double *xarr, double *yarr, double x, int n, int k);

#endif // INTERPOL_H
