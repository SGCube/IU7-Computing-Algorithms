#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

void clear_matrix(double **a, int n);

void free_matrix(double **a, int n);

double **read_matrix(FILE *f, int *k);

void print_matrix(double **plist, int n, int m);

double **calloc_matrix(int n, int m);

#endif // MATRIX_H
