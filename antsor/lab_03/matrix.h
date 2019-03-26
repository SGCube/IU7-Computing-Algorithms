#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

void clear_matrix(double **a);

double **read_matrix(FILE *f, int kx, int ky);

void print_matrix(double **matrix, int kx, ky);

#endif // MATRIX_H
