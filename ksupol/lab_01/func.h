#ifndef __FUNC__H__
#define __FUNC__H__

//функция, выделяющая память под матрицу
double **allocate_matrix(int n, int m);

//функция заполнения матрицы
int read_matrix(double ***matrix, int n, FILE *f);

//функция вывода матрицы на экран
void print_matrix(double **matrix, int n, int m);

//функция чтения из файла
int read_from_file(FILE *f, int *amount, double ***matrix);

//функция освобождения памяти из-под матрицы
void free_matrix(double **matrix);

//функция сортировки матрицы
void sort(int n, double **matrix);

//функция нахождения интервала
int find_interval(int n, int a, double **matrix, double x, 
		int *up, int *down);
		
double **diff(double **matrix, int up, int down, int n);

void interpolate(double **result, int n, double x, double **matrix);
#endif