#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

void clear_matrix(double **a, int n);

double **read_matrix(FILE *f, int *k);


void print_matrix(double **plist, int k);

#endif // MATRIX_H
