#ifndef INTERPOL_H
#define INTERPOL_H

int cmp_point_x(void *p1, void *p2);

double **surround(double plist[][2], double x, int n, int k);

double newton(double x, int n, double *parr);

double solve(double plist[][2], double x, int n, int k);

#endif // INTERPOL_H
