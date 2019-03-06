#ifndef FILEIO_H
#define FILEIO_H

#include <cstdio>

void clear_matrix(double **a, int n);

double **read_matrix(FILE *f, int *k);

#endif // FILEIO_H
