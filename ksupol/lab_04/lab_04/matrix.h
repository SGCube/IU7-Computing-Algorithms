#include <stdio.h>
#ifndef MATRIX_H
#define MATRIX_H

//функция, выделяющая память под матрицу
double **allocate_matrix(int n, int m);

//функция заполнения матрицы
int read_matrix(double ***matrix, int n, FILE *f);

void free_matrix(double **matrix);

#endif // MATRIX_H
