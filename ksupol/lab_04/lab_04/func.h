#ifndef FUNC_H
#define FUNC_H

int read_from_file(FILE *f, int *amount, double ***matrix);

double F(double x, int k);

double **solve(double **matrix, int amount, int n);

double **get_slau_matrix(double **table, int amount, int n, double **col);

void subtract_above(double **matrix, double **id, int n, int x);

void subtract_below(double **matrix, double **id, int n, int x);

void devide(double **matrix, int n, int i, double denominator);

void swap_lines(double **matrix, double **id, int n, int i, int j);

double *mult(double **mat_a, double *col, int am);
#endif // FUNC_H
