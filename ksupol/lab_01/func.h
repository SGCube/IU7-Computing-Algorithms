#ifndef __FUNC__H__
#define __FUNC__H__

//функция чтения из файла
int read_from_file(FILE *f, int *amount, double ***matrix);

//функция сортировки матрицы
void sort(int n, double **matrix);

//функция нахождения интервала
int find_interval(int n, int a, double **matrix, double x, 
		int *up, int *down);
		
double **diff(double **matrix, int up, int down, int n);

void interpolate(double **result, int n, double x, double **matrix);
#endif