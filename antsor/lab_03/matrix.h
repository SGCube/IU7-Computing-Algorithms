#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

struct Matrix
{
    double **matr;
    int size_x;
    int size_y;

    Matrix();
    ~Matrix();

    void read(FILE *f, int kx, int ky);
    void print();
    void clear();
};

#endif // MATRIX_H
