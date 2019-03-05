#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>

void clear_matrix(double **a, int n);

double **read_matrix(std::ifstream f, int *k);

#endif // FILEIO_H
