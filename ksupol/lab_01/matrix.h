#ifndef __MATRIX__H__
#define __MATRIX__H__

//функция, выделяющая память под матрицу
double **allocate_matrix(int n, int m);

//функция заполнения матрицы
int read_matrix(double ***matrix, int n, FILE *f);

//функция вывода матрицы на экран
void print_matrix(double **matrix, int n, int m);

//функция освобождения памяти из-под матрицы
void free_matrix(double **matrix);

#endif