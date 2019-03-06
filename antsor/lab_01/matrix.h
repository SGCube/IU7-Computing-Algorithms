#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
using namespace std;

void clear_matrix(double **a, int n);

double **read_matrix(ifstream &f, int *k);

#endif // FILEIO_H
