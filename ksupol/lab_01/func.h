#ifndef __FUNC__H__
#define __FUNC__H__

// функция, выделяющая память под матрицу
double **allocate_matrix(int n, int m);

// функция заполнения матрицы
int read_matrix(double ***matrix, int n, FILE *f);

void print_matrix(double **matrix, int n, int m);

int read_from_file(FILE *f, int *amount, double ***matrix);

void free_matrix(double **matrix);

#endif