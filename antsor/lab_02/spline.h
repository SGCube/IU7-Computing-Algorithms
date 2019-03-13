#ifndef SPLINE_H
#define SPLINE_H

int cmp_point_x(const void *p1, const void *p2);

double *sle(double **matr, int n);

double **spline(double **plist, int n);

double solve(double **plist, double x, int n);

#endif // INTERPOL_H
